# Introduction #

This page describes plans to rework the communication between RT Ops, the GUI, and the Controller Manager. These plans also include a rework of the state machine inside RT Ops and a change to the main loop in the connectors.

# Purpose #

There are a couple of reasons for this rewrite. The first is that it will allow for RT\_PREEMPT support, which will allow us to run the system on a far wider variety of computers. Second, it'll clean up RT Ops's state machine, allowing for soft shutdown controllers.

Here is a list of the benefits of the rewrite:
  * Simplify threading. By using one realtime thread instead of two, we should be able to improve performance (by decreasing context switches) and make RT Ops simpler.
  * Enable RT\_PREEMPT support -- By using a single realtime thread, we'll be able to adequately instrument our code to find errors that break our realtime under RT\_PREEMPT. RT\_PREEMPT support will remove the dependency on RTNet, which is poorly maintained and crashes at startup on some of our machines.
  * Shutdown controller support -- Currently, we cannot implement soft shutdown due to the complexity of RT Ops's state machine. The New Event System will implement support for this.
  * Remove the Controller Manager's state machine -- The primary source of crashes in our current system is the controller manager's state machine, which has extremely difficult-to-debug threading code. This code is central to our current system, but isn't actually necessary, since RT Ops implements all the same functionality.
  * Allow usage of EtherLabs's EtherCAT Master -- Some of our EtherCAT issues may stem from SOEM (admittedly, I have not verified this). EtherLabs's master does not support Xenomai, so until we can operate under RT\_PREEMPT, we're stuck with SOEM.

# Overview #

The controller manager will be responsible for loading/unloading controllers and enabling/disabling logging. It will no longer care about the robot's enabled/disabled state.

RT Ops will get a new state machine, fixing some fundamental issues, and cleaning it up.

There will be a new component, the Event Manager, which will sit between RT Ops, the CM, and the GUI. Its purpose will be to receive events from RT Ops and forward them to the correct components from there. It will also output diagnostic messages when high importance events occur.

# Communication #

The GUI will have an output port through which it will send state requests to RT Ops and one through which it will send watchdog updates. It will also have an output port through which it will send controller load/unload and logging requests to the CM. The GUI will receive acknowledgements for controller load/unload and logging requests from the CM. The acknowledgements from RT Ops will be described later.

The Event Manager will have one input port, through which it will receive RT Ops events. It will have one output port to the CM and one to the GUI through which it will forward events.

The CM will also have a port to RT Ops through which it'll send controller load/unload requests. RT Ops will respond through a "CM Ack" event.

RT Ops sends the full robot state to the GUI at 50 Hz, and outputs a separate, more minimal, type for logging a 1kHz

# RT Ops's State Machine #

RT Ops's state machine will no longer be concerned with whether or not a controller is loaded -- that will be handled separately. Each heading below is one state in RT Ops's state machine:

## Disabled ##
In the disabled state, the robot is... disabled.

### Transitions ###
The Disabled state may transition into Enabled, which will happen if the GUI sends an Enabled request and the controllers are outputting an Enabled state.

## Enabled ##
In the Enabled state, the controller's torque commands are sent to the amplifiers. A controller must be loaded while in this state.

### Transitions ###
This state may transition to eStop, Halt, or Stop states.

Enabled will transition to eStop or Halt states as a result of the activation of safety systems.

Enabled will transition to eStop if either the GUI or the Controller command the eStop state.

Enabled will transition to Halt if the controller commands the Halt state.

Enabled will transition to if either the GUI or Controller command the Stop state.

## Halt ##
In this state, RT Ops will command the Medullas into their halt states.

### Transitions ###
Halt may only transition to eStop state. This transition will occur if the GUI commands the eStop state, the controller commands an eStop state, or a Medulla goes into eStop.

## eStop ##
In this state, RT Ops will command the Medullas into their eStop states.

### Transitions ###
eStop may only transition into Reset state. This transition will happen as a result of the GUI commanding the Reset state.

## Reset ##
In this state, RT Ops will send the Medullas a reset command.

### Transitions ###
Reset may only transition to Disabled. This transition will automatically occur after all Medullas have entered the Idle state.

## Stop ##
In this state, RT Ops runs damping on all the motors for a smooth shutdown.

### Transitions ###
Stop may transition to eStop, Halt, or Disabled states.

Stop will transition to eStop or Halt upon the activation of safeties, or if commanded by the GUI or controller.

Stop will transition to Disabled once all the medullas are in the idle state.

# Acknowledgements #
There will be two acknowledgement event types, one for each of the GUI and the Controller Manager.

## Controller Manager ##
When the Controller Manager notifies RT Ops that a controller has been loaded, it should try to connect with the controller and respond with an event indicating success or failure.

When the Controller Manager requests a controller unload, RT Ops should cease calling the controller, then respond with an acknowledgement event.

## GUI ##
When the GUI sends a state request, RT Ops will send back an acknowledgement event. After the acknowledgement is sent, RT Ops should not execute any more decisions using the previous state request; the acknowledgement must be sent before RT Ops makes decisions based on the new state request.

If the new state request causes any state transitions, then a separate event should be triggered notifying the GUI that it triggered RT Ops's state to transition.