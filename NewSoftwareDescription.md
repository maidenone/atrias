# Introduction #

This page lists the various components of the new system and how they interact.

# GUI #

The GUI is the only component that does not necessarily run on the robot control computer. It contains code that is not specific to any controllers as well as the ability to load controller-specific GUIs and communication code.

The GUI communicates with the Controller Manager to command robot states, and receive information on the Controller Manager's status. It also lists to a ROS topic published by RTOps to update the status gui and the caret.

The controller-specific component of the GUI may talk with the controllers as well, to send over new parameter sets and receive information back from the controller.

# Controller Manager #

The Controller Manager contains a state machine that controls the controller load/unload system. This also handles enabling and disabling controllers.

The Controller Manager communicates with the GUI, as described above, as well as with RT Ops. The Controller Manager sends commands to RT Ops for enabling/disabling/eStop and receives "events", which inform the Controller Manager when something's happened that it or the GUI needs to pay attention to.

The Controller Manager is also responsible for loading and unloading the controllers as well as enabling and disabling logging.

# RT Ops #

RT Ops handles everything that must occur in realtime that doesn't belong in a controller or connector. This includes basic logging, the controller main loop, safeties, and timestamp distribution.

RT Ops communicates with the Controller Manager and GUI as described above. It communicates with a Connector to read in a robot state and send out commands. RT Ops also calls functions in the top-level controller to execute it, and exposes operations for retrieving accurate timestamps.

# Connector #

A Connector handles the communication between RT Ops and the "robot", whatever that robot may be. There are multiple Connectors (currently, there is the EtherCAT connector, the Simulation Connector, the No-Op Connector, and the nonfunctional EtherLabs connector).

A Connector calls an operation inside RT Ops to send it a new robot state and exposes an operation that RT Ops calls to send the output back to the "robot". Additionally, the connector may call an operation in RT Ops to report an event to the Controller Manager and GUI.

# Top-level Controller #
The top-level controller handles the logic flow for controlling the robot. It exposes an operation to RT Ops, taking in the robot state and returning a command. When the Controller Manager is in its "Enabled" state, the controller commands the Medullas' states, allowing it to eStop, halt, or disable the robot if it chooses to.

For modularity, a top-level controller may assign tasks to sub-controllers, such as a PD controller for motor position.

# Sub-controller #
A sub-controller is a controller that may be created and called by a top-level controller. A sub-controller provides one capability, which may be shared by multiple top-level controllers. This adds modularity to the controller structure.