# Diagram #
The diagram below shows all the state transitions for the Medullas. The colors of the states indicate the color of the Medulla's LED while it is in that state.

![http://atrias.googlecode.com/svn/wiki/MedullaStates.png](http://atrias.googlecode.com/svn/wiki/MedullaStates.png)

# Idle #
LED: green

ID: 0

This is the state the Medulla starts in. The Medulla may only transition to init state from idle state. This transition is initiated by commanding a state of run.

# Init #
LED: Cyan

ID: 1

In this state, error conditions are checked for then the amplifier is enabled. This state may transition to run or error. If error conditions are detected, it goes to error prior to enabling the amplifier; if not, the amplifier is enabled and the state immediately switches to run.

# Run #
LED: Blue

ID: 2

This is the state where the Medulla is fully operational. The outputs are enabled, and the robot is running. This state may transition to stop, halt, or error state.

Transition to stop state may be initiated by commanding stop or idle state.

Transition to halt state may be initiated by commanding halt state or automatically if the medulla detects that a halt is needed.

Transition to error state may be initiated by commanding error state, if a limit switch is hit, if the eStop is activated, or if any other error conditions are detected.

# Stop #
LED: Violet

ID: 3

In stop state, the amplifier is disabled. Stop state immediately transitions into idle state.

# Halt #
LED: Yellow

ID: 4

In halt state, the Medulla attempts to stop its motor as rapidly as possible. As soon as the motor stops (or reverses slightly), it drops its output to 0. Halt state will transition automatically to error state after a 100 ms timeout, through a command for error, if a limit switch is activated, if the eStop is activated, or if any other error conditions are detected.

# Error #
LED: Red

ID: 5

The error state is the state the Medulla goes into when the eStop is activated. It may only transition to reset state. This transition is initiated by commanding the reset state.

# Reset #
LED: White

ID: 6

Reset is a state allowing the Medulla to leave error state. Reset state immediately leads to idle state.

# Watchdog Timeout #
LED: Off

ID: 7

This state isn't shown on the diagram. It may be entered from any other state. This is entered when a code lock-up is detected. In this state, the PWM for the amplifier is disabled (like error state).