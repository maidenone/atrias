// Devin Koepl

#include <atrias_controllers/demo_controller.h>

#define MID_MOT_ANG_A	 -1.0254
#define MID_MOT_ANG_B		4.167
#define F_SLOW .1

typedef struct
{
	float time;
} SineData;

void initialize_demo_controller(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data)
{
	DEMO_CONTROLLER_STATE(state)->time = 0.;

	output->motor_torqueA = output->motor_torqueB = output->motor_torque_hip = 0.;

	DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang = 0.0; 
	DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang_vel = 0.0;
	DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len = 0.0;
	DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len_vel = 0.0;
	
	DEMO_CONTROLLER_STATE(state)->currentState = DEMO_STATE_STOPPED;
	DEMO_CONTROLLER_STATE(state)->currentDemo = DEMO_CONTROLLER_DATA(data)->commandedDemo;
}


void update_demo_controller(ControllerInput *input, ControllerOutput *output, ControllerState *state, 
	ControllerData *data)
{
	// We use a constant timestep of 1ms because this is the rate that this function is actually being called at.
	DEMO_CONTROLLER_STATE(state)->time += 0.001;

	if (DEMO_CONTROLLER_STATE(state)->currentState == DEMO_STATE_STOPPED)
	{
		// If the current state is stopped then we can switch to another controller
		DEMO_CONTROLLER_STATE(state)->currentDemo = DEMO_CONTROLLER_DATA(data)->commandedDemo;

		if (DEMO_CONTROLLER_DATA(data)->commandedState == 1) 
		{
			DEMO_CONTROLLER_STATE(state)->time = 0.;
			DEMO_CONTROLLER_STATE(state)->currentState = DEMO_STATE_STARTING;
			printk("ENABLING\n");
		}
	}

	else if (DEMO_CONTROLLER_STATE(state)->currentState == DEMO_STATE_STARTING)
	{
		start_demo(input, output, state, data);
	}

	else if (DEMO_CONTROLLER_STATE(state)->currentState == DEMO_STATE_RUNNING)
	{
		if (DEMO_CONTROLLER_STATE(data)->currentDemo == DEMO1)
			DEMO_CONTROLLER_STATE(state)->desiredPos = demo1(input, output, state, data, DEMO_CONTROLLER_STATE(state)->time);
		if (DEMO_CONTROLLER_STATE(data)->currentDemo == DEMO2)
			DEMO_CONTROLLER_STATE(state)->desiredPos = demo2(input, output, state, data, DEMO_CONTROLLER_STATE(state)->time);
		if (DEMO_CONTROLLER_STATE(data)->currentDemo == DEMO3)
			DEMO_CONTROLLER_STATE(state)->desiredPos = demo3(input, output, state, data, DEMO_CONTROLLER_STATE(state)->time);
		if (DEMO_CONTROLLER_STATE(data)->currentDemo == DEMO4)
			DEMO_CONTROLLER_STATE(state)->desiredPos = demo4(input, output, state, data, DEMO_CONTROLLER_STATE(state)->time);
			

		// If we are currently running a demo and the stop demo button is pressed, go to demo_stopping
		if (DEMO_CONTROLLER_DATA(data)->commandedState == 0)
			DEMO_CONTROLLER_STATE(state)->currentState = DEMO_STATE_STOPPING;
	}

	else if (DEMO_CONTROLLER_STATE(state)->currentState == DEMO_STATE_STOPPING)
	{
		stop_demo(input, output, state, data);
	}


	// If we are not in the stopped state, then decode the desired leg angle, leg length, and hip angle into motor torques
	if (DEMO_CONTROLLER_STATE(state)->currentState != DEMO_STATE_STOPPED) 
	{
		float des_mtr_angA = DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang - PI + acos(DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len);
		float des_mtr_angB = DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang + PI - acos(DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len); 

		float des_mtr_ang_velA = -DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len_vel / 2. / sin(des_mtr_angA - des_mtr_angB) - DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang_vel / 2.;
		float des_mtr_ang_velB = DEMO_CONTROLLER_STATE(state)->desiredPos.leg_len_vel / 2. / sin(des_mtr_angA - des_mtr_angB) - DEMO_CONTROLLER_STATE(state)->desiredPos.leg_ang_vel / 2.;

		output->motor_torqueA = DEMO_CONTROLLER_DATA(data)->p_gain * (des_mtr_angA - input->motor_angleA) 
			+ DEMO_CONTROLLER_DATA(data)->d_gain * (des_mtr_ang_velA - input->motor_velocityA);
		output->motor_torqueB = DEMO_CONTROLLER_DATA(data)->p_gain * (des_mtr_angB - input->motor_angleB) 
			+ DEMO_CONTROLLER_DATA(data)->d_gain * (des_mtr_ang_velB - input->motor_velocityB);

		output->motor_torque_hip = DEMO_CONTROLLER_DATA(data)->hip_p_gain * (DEMO_CONTROLLER_STATE(state)->desiredPos.hip_ang - input->hip_angle) 
			+ DEMO_CONTROLLER_DATA(data)->hip_d_gain * (DEMO_CONTROLLER_STATE(state)->desiredPos.hip_ang_vel - input->hip_angle_vel);
	}
	else
	{
		output->motor_torqueA = 0.0;
		output->motor_torqueB = 0.0;
		output->motor_torque_hip = 0.0;
	}

}

void start_demo(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data)
{
	printk("Starting Demo\n");

	// If we are at the staring position then go to the running state
	if (1)
	{
		DEMO_CONTROLLER_STATE(state)->time = 0.;
		DEMO_CONTROLLER_STATE(state)->currentState = DEMO_STATE_RUNNING;
	}
}

void stop_demo(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data)
{
	printk("Stopping Demo\n");

	// If we are at the zero position, then go to the stopped state
	if (1)
	{
		DEMO_CONTROLLER_STATE(state)->time = 0.;
		DEMO_CONTROLLER_STATE(state)->currentState = DEMO_STATE_STOPPED;
	}
}

RobotPosition demo1(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data, float time)
{
	printk("Running Demo 1\n");
	RobotPosition desPos;

	desPos.leg_len = 0.;
	desPos.leg_len_vel = 0.;
	desPos.leg_ang = 0.;
	desPos.leg_ang_vel = 0.;
	desPos.hip_ang = 0.;
	desPos.hip_ang_vel = 0.;

	return desPos;
}

RobotPosition demo2(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data, float time)
{
	printk("Running Demo 2\n");
	RobotPosition desPos;

	desPos.leg_len = 0.;
	desPos.leg_len_vel = 0.;
	desPos.leg_ang = 0.;
	desPos.leg_ang_vel = 0.;
	desPos.hip_ang = 0.;
	desPos.hip_ang_vel = 0.;

	return desPos;
}

RobotPosition demo3(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data, float time)
{
	printk("Running Demo 3\n");
	RobotPosition desPos;

	desPos.leg_len = 0.;
	desPos.leg_len_vel = 0.;
	desPos.leg_ang = 0.;
	desPos.leg_ang_vel = 0.;
	desPos.hip_ang = 0.;
	desPos.hip_ang_vel = 0.;

	return desPos;
}

RobotPosition demo4(ControllerInput *input, ControllerOutput *output, ControllerState *state, ControllerData *data, float time)
{
	printk("Running Demo 4\n");
	RobotPosition desPos;

	desPos.leg_len = 0.;
	desPos.leg_len_vel = 0.;
	desPos.leg_ang = 0.;
	desPos.leg_ang_vel = 0.;
	desPos.hip_ang = 0.;
	desPos.hip_ang_vel = 0.;

	return desPos;
}

void takedown_demo_controller(ControllerInput *input, ControllerOutput *output, ControllerState *state, 
	ControllerData *data)
{
	output->motor_torqueA = output->motor_torqueB = output->motor_torque_hip = 0.;
	DEMO_CONTROLLER_STATE(state)->des_leg_ang = 0.0; 
	DEMO_CONTROLLER_STATE(state)->des_leg_ang_vel = 0.0;
	DEMO_CONTROLLER_STATE(state)->des_leg_len = 0.0;
	DEMO_CONTROLLER_STATE(state)->des_leg_len_vel = 0.0;
}