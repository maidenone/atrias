/*
 * controller_core.cpp
 *
 * Leg Force Controller
 *
 *  Created on: May 5, 2012
 *      Author: Michael Anderson
 */

#include <ac_leg_force/controller_core.h>

ControllerInitResult controllerInit() {
	//ringBufferLocation = 0;

	// DEBUG! States for debugging the "chirping"
	chirp_on = 0;
	//elapsed_time = 0;
	// END DEBUG

	ControllerInitResult cir;
    cir.controllerInputSize = sizeof(InputData);
    cir.controllerStatusSize = 0;
    cir.error = false;
    return cir;
}

void controllerUpdate(robot_state state, ByteArray input, ControllerOutput *output, ByteArray &status) {
    InputData *id = BYTE_ARRAY_TO_STRUCT(input, InputData*);

	// Values for safety limits.  If outside of these, a damping controller engages

	// Leg length limits
	float safety_length_long = 0.97;
	float safety_length_short = 0.4;

	//  Motor A angle limits
	float safety_angleA_short = -2./3.*PI;
	float safety_angleA_long = 0.;

	// Motor B angle limits
	float safety_angleB_short = PI;
	float safety_angleB_long = 5./3.*PI;

	// Leg length calculation
	float leg_length = cos((2.0 * PI + state.leg_angleA - state.leg_angleB ) / 2.0);



	// We control the hip the same in flight and stance, the equation is based on experimental test to prevent lateral forces on the knee joints.
	float desired_hip_angle = 0.99366 * state.body_angle + 0.03705;
	desired_hip_angle = CLAMP(desired_hip_angle, -0.2007, 0.148);

	// Hip gains.  Hard coded and well-tested with hopping. 2012-02-26
	float hip_p_gain = 2000.;
	float hip_d_gain = 20.;

	// Hip PD control.
	output->motor_torque_hip = hip_p_gain * (desired_hip_angle - state.motor_angle_hip) - hip_d_gain * state.motor_velocity_hip;



	// If outside of safety limits, Engage damping controller
	// Logic:  if value is not equal to its "CLAMPED" value, it must be out of range
	if(leg_length != CLAMP(leg_length, safety_length_short, safety_length_long) ||
		state.motor_angleA != CLAMP(state.motor_angleA, safety_angleA_short, safety_angleA_long) ||
		state.motor_angleB != CLAMP(state.motor_angleB, safety_angleB_short, safety_angleB_long))
	{
		// Damping controller engages, with hard-coded gains
		output->motor_torqueA = - 100.0 * state.motor_velocityA;
		output->motor_torqueB = - 100.0 * state.motor_velocityB;
	}
	// Else, engage normal controller
	else
	{
		// Get values from GUI.
		float desired_force = id->spring_deflection*9.81;
		float FORCE_P_GAIN = id->p_gainA;
		float FORCE_D_GAIN = id->d_gainA;
		float FORCE_I_GAIN = id->i_gainA;

		// Calculate spring deflections.
		float spring_defA = state.motor_angleA - state.leg_angleA;
		float spring_defB = state.motor_angleB - state.leg_angleB;

		// Known Values
		float MOTOR_CONSTANT = 0.12226; // Nm per A
		//float SPRING_CONSTANT = 310.; // A per rad  via rough calibration 2012-03-01
		float SPRING_CONSTANT = 1175.*1.108; // Nm per rad  via spring tester 2012-03-28
		float GEAR_RATIO = 50.;

		// Using the current leg configuration, converts the desired axial force into a desired leg torque
		float desired_torque = 0.5*desired_force*cos(PI + asin(leg_length));

		// Inverse spring function:  Converts desired torques into desired deflection angles.
		//		float desired_spring_def = desired_torque/(MOTOR_CONSTANT*SPRING_CONSTANT*GEAR_RATIO);
		float desired_spring_def = desired_torque/(SPRING_CONSTANT);

		// NOTE: defA is NEGATIVE when compressed.  Should be opposite sign of defB.
		state.desired_spring_defA = desired_spring_def;
		state.desired_spring_defB = -1.0*desired_spring_def;

		// Leg A, PD control.
		state.desired_motor_angleA = state.motor_angleA + (state.desired_spring_defA - spring_defA);
		output->motor_torqueA = (FORCE_P_GAIN * (state.desired_motor_angleA - state.motor_angleA)) - (FORCE_D_GAIN * (state.motor_velocityA)) + (FORCE_I_GAIN * spring_defA);

		// Leg B, PD control.
		state.desired_motor_angleB = state.motor_angleB + (state.desired_spring_defB - spring_defB);
		output->motor_torqueB = (FORCE_P_GAIN * (state.desired_motor_angleB - state.motor_angleB)) - (FORCE_D_GAIN * (state.motor_velocityB)) + (FORCE_I_GAIN * spring_defB);
	}

	//**********************************************
	//***********DEBUG "CHIRP" TESTING**************
	//**********************************************

	// Attempts to recreate intermittent chirping or squeaking sound during loading

	// Store values from gui
	float chirp_freq = id->p_gainB;
	float amplitude = id->d_gainB;
	float tempo = id->i_gainB;

	// Computes periods for resting and chirping
	float sig_period = 1.0 / chirp_freq * 1000.;
	float tempo_period = 60. / tempo * 1000.;

	// Declare superimposed chirp torque signal
	float chirp_torque;

	// Increment Time Variable
	elapsed_time += 1;

	// If "resting"
	if(chirp_on == 0)
	{
		if(elapsed_time > tempo_period)
		{
			chirp_on = 1;
			elapsed_time = 0;
		}

		// Resting, so set chirp torque to zero
		chirp_torque = 0;

	}
	// Else, it is "playing"
	else
	{
		if(elapsed_time > sig_period)
		{
			chirp_on = 0;
			elapsed_time = 0;
		}

		chirp_torque = amplitude*sin(2.*PI*chirp_freq*elapsed_time/1000.);
	}
	output->motor_torqueA += chirp_torque;
	output->motor_torqueB += chirp_torque;

	//**************************************************
	//***********END DEBUG "CHIRP" TESTING**************
	//**************************************************
}

void controllerTakedown() {

}