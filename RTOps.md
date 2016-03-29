# Duties #

RTOps's purpose is to handle anything that needs to occur in realtime and is not the job of either a controller or a connector. This includes:
  * The main controller loop
  * Non-controller-specific logging
  * Anything needed for realtime (memory locking, etc).
  * Safeties
  * A state machine
  * Handling and distribution of timestamps

## Controller Loop ##

The controller loop code is in ControllerLoop.cpp. The loop therein is supposed to run each time a new robot state is available -- this includes immediately re-running if the previous cycle overshot and a new robot state is available. This is achieved with an Orocos Semaphore.

This loop makes its own copy of the robot state, and also updates the TimestampHandler with a new timestamp. The ControllerLoop class is also responsible for dealing with loaded/unloaded controllers -- if a controller is loaded, the loop calls that controller each time.

The controller loop will zero torques if the commanded state for the medullas is not run, and clamps the torques otherwise. It then calls the connector to send the new controller outputs to the robot.

## Logging ##

RT Ops's logging happens in the OpsLogger class. This class is responsible for synchronizing logging data from RT Ops.

The logger actually sends an RtOpsCycle for logging when it receives a new robot state. However, that RtOpsCycle contains data from the last cycle, not the new cycle. This is to synchronize the robot state with the controller output as well as to allow "starting" and "ending" times to be calculated (these times do not include time spent in the connector).

The logger is also capable of sending out "events." Events allow RT Ops to inform the Controller Manager of happenings within RT Ops, such as a triggered eStop, state machine change, acknowledgments for new state commands, and other miscellaneous alerts. Events can also contain a byte of metadata, allowing additional information to be contained in the report. The full list of event types can be found in the RtOpsEvent enum in atrias\_shared/globals.h

## Realtime handling ##

The RTHandler class has the duty of maintaining realtime. Currently, this only involves locking/unlocking memory and registering a signal handler.

The signal handler it registers is for SIGXCPU, which is sent by Xenomai whenever realtime code undergoes a mode switch. This signal causes spamming on the console. We hope to be able to find the root of the problem, but for now this workaround is working. See [issue 93](https://code.google.com/p/atrias/issues/detail?id=93).

## Safety ##

The Safety class is responsible for triggering safeties. This includes checking each actuator to see if a collision might occur, and commanding a halt mode if necessary. Additionally, the safety class will monitor the hips as they relax during a halt, and command an eStop if they are not behaving as expected.

Eventually (probably with the upcoming GUI rewrite), we wish for the GUI to control which safeties are enabled and which are disabled. The Safety class will be responsible for keeping track of this information as well.

## State Machine ##

The StateMachine class contains RTOps's state machine. This state machine drives the actual command sent to the medullas, and is the same state sent to the controllers. The states in this machine may be found in atrias\_shared/globals.h

## Timestamps ##

The TimestampHandler class has the responsibility of holding the "current" timestamp. This timestamp is updated by the controller loop, and should always reflect the timestamp from the current controller cycle.

This allows controllers to easily access the timestamp, either as a ROS header or in Orocos's nanoseconds unit.

# New Event System #
This section describes RT Ops as planned for the new event system rewrite.

## CMHandler ##
This will handle all communication to/from the controller manager.

Status: Not started

## Controller Handler ##
This will call the controller (if loaded), and hold a copy of the controller's output.

Status: Not started

## GUIHandler ##
This will handle all communication to/from the GUI (allowing access to the GUI's commands).

Status: Done

## Main Loop ##
The MainLoop class will run RTOps's main realtime loop. This will expose an operation to the connectors that takes in a robot state and returns a controller output. It makes calls to the other RT Ops subsystems in the proper order.

Status: In progress

## Ops Logger ##
The OpsLogger class will be largely unchanged -- it will handle the logging and event sending for RT Ops.

Status: In progress

## Output Handler ##
The OutputHandler class will set the command field in the final controller output, as well as run the stop controller if necessary.

This will contain a copy of the controller output, but modified to be ready to return to the Connector (i.e. torques zeroed/stop controller/ final medulla\_state\_t command).

Status: Not started

## Rt Handler ##
This will do everything necessary to get realtime / work around Xenomai and other bugs.

Status: Not started

## Rt Printer ##
This class will allow RT Ops and other components to print out messages in a realtime-safe manner. It will do this by deferring the printing to another thread by using an Operation.

Status: Done

## Safety ##
This will calculate when a transition to the E\_STOP or Halt state is necessary.

Status: Not started (will port from master branch)

## State Machine ##
This will run the main RT Ops state machine. It will no longer be responsible for calculating the medulla command, which will now be done by the OutputHandler

Status: In progress