# Introduction #

After the robot is disassembled it is important to test that all the important sensors are connected properly, working, and tested. This page lists steps required to verify sensors before enabling robot.

  1. Calibrate Leg encoders
    * Lock motors in place with using calibrations bolts
    * Remove comments on lines 239, 244, 251, 256, 263, 268, 275, 281 of atrias\_medulla\_drivers/src/LegMedulla.c to enable printing of raw encoder values.
    * Recompile atrias\_medulla\_drivers packages (`rosmake atrias_medulla_drivers`)
    * Run control system (`sudo roslaunch atrias orocos_ecat.launch`)
    * Record raw encoder values into left and right leg calibration files (The appropriate files are listed on lines 8 and 12 of robot\_definitions/bipedX\_variant\_defs.h)
  1. Verify absolute leg encoder directions are correct.
    * Run control system with GUI.
    * Move all leg joints and verify that leg graphic in GUI matches movement of leg.
    * If it does not match, change sign of RAD\_PER\_CNT constant for that motor in leg calibration file
  1. Check incremental encoders are connected properly and working
    * Run control system (GUI not required)
    * run: `rxplot /gui_robot_state_in/robotState/lLeg/halfA/rotorAngle` to plot rotor encoder A values.
    * Move left A motor and verify that encoder value changes appropriately
    * Repeat process for all motors replacing lLeg with rLeg for right leg values and halfA with halfB for A and B motors.
  1. Test limit switches
    * With control system running, run: `rostopic echo /gui_robot_state_in | grep "limitSwitches"`
    * With no switches pressed, zeros should be printed to the screen.
    * Press each limit switch and verify that a value changes on the screen when the switch is pressed.
  1. Test absolute hip encoders
    * With control system running execute: `rxplot /gui_robot_state_in/robotState/lLeg/hip/absoluteBodyAngle`
    * Moving left hip actuator into body (toe outwards) should result in a positive change in hip angle
    * With left leg vertical hip angle should be approximately 4.71239
    * Test right hip by running `rxplot /gui_robot_state_in/robotState/rLeg/hip/absoluteBodyAngle`
    * Moving right hip actuator into body (right toe outwards) should decrease the right hip angle
    * With right leg vertical to body, hip angle should also read approximately 4.71239
  1. Test incremental hip encoders
    * With control system running, run: /gui\_robot\_state\_in/robotState/lLeg/hip/legBodyAngle
    * Results should be the same as test above when leg is moved. If encoder is not working, you will only see a very slow change in angle caused by the correction filter.
    * Repeat for right leg (`/gui_robot_state_in/robotState/rLeg/hip/legBodyAngle`)