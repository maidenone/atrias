# Objective #

The initialization procedure should

  * move the robot from any arbitrary **valid** state into a _desired state_ (position and velocity)
  * result in smooth initialization motion and smooth transition into "controlled" motion
  * have all safety mechanisms active
  * allow for easy inclusion and customization
  * abstraction to initialize robot poses / robot states (COM position / velocity)


# Requirements #

  * define desired state in TLC


# possible Implementations #

## Method #1 ##
The start scripts for TLCs wanting initialization could additionally load a startup controller (as its own component), which would be identified by its own service ("startupController" or something like that). After the TLC is loaded, RT ops would check if this service exists (note: I'm assuming Orocos provides this capability).

Shutdown controllers could be handled similarly, or there could simply be one automatic shutdown controller (damping on hips until they reach the hard stops). I'm not sure we need as much versatility in shutdown controllers as in startup controllers.

Each cycle, RT Ops would call each loaded controller (TLC, startup, and shutdown).`*` After running each controller, RT Ops would then command the output from the currently "selected" controller, according to its internal state machine (with a likely exception for ERROR and HALT commands).

Each controller would signal RT Ops that it's done running through the "command" field of its output. RT Ops's state machine would then cycle to the next relevant state (this would include consideration of the Controller Manager's command, as well).

`*` Note: we could potentially split up the operations for when each controller is disabled or enabled, or keep them as-is.

### Pros ###
Extremely simple implementation in controllers (just load the startup controller, no need to make your own state machine).

Capable of running startup controllers beyond the basic per-actuator state-commanding startup controller.

### Cons ###
Limited to 1 startup controller and 1 shutdown controller, so it cannot cleanly handle arbitrarily long sequences of startup controllers.


## Method #2 ##
A deploy.lua script would launch a [Lua finite state machine](http://www.orocos.org/wiki/orocos/toolchain/luacookbook#toc48).  RT Ops would request state transitions (to start, run, stop) but would not control them; however, it would still control the commanded current.

### Details ###
Controller Side:

deploy.lua
  * Runs the fsm lua supervisor
  * Runs the lua controller component (launch\_fsm.lua)
launch\_fsm.lua
  * configureHook: Sets up peers
  * updateHook:    Runs the finite state machine (fsm.lua)
  * cleanupHook:   Shuts down peers
fsm.lua
  * We can decide what main states we want the controllers to have
  * The controller can use any number of internal states


RTops Side:
  * Calls the supervisor's "events" port to set the fsm state
  * Calls the updateHook of launch\_fsm.lua to run the fsm
  * Recieves the new controller output on an event port
  * Sends the robot state to the controller on a port or as a property when requested


### Pros ###
This is the most modular architecture.  Any combination of controllers could be run, and there is no imposed controller structure.

The controller has full visibility and control of when states are switched.

### Cons ###
It's not the way the current system is set up.  The trick is how to point RT Ops to the service it is supposed to run (maybe run the state machine as a service?).  This needs to be determined.