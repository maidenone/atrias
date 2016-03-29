Note: This page describes the tasks of the Controller Manager in the New Event System, not the existing system.

# Overview #

The Controller Manager has 5 subsystems. It does everything necessary for realtime (RTHandler), starts and stops logging (LoggingManager), and loads/unloads controllers (ControllerLoader), and has subsystems for communicating with the GUI and RTOps.

The Controller Manager should operate asynchronously, doing everything in a single thread (if possible). This should simplify the threading considerably compared to the old threaded EventManager setup.

# RTHandler #

The RTHandler takes various steps to ensure realtime. These include:
  * Locking memory
  * Dropping priorities of other processes
  * Increasing priorities for IRQs, if requested by a connector
  * Disabling CPU frequency scaling, if enabled
  * Preventing the processor from going to sleep, if enabled
  * Working around Xenomai/Orocos bugs, if necessary

The only steps needed for HRT (hard realtime) operation that are not done by the RTHandler are setting the thread priority and prefaulting the stack, which must by done by the connector. Note: There should be a library in atrias\_shared for prefaulting the stack.

# LoggingManager #
The Logging Manager starts and stops logging at the GUI's request. If this cannot reasonably be done from C++, then we'll keep on using the current Python-based logger.

# ControllerLoader #
This subsystem is responsibly for loading and unloading controllers. It also communicates with RT Ops, so as to allow it to connect to controllers and after loading and disconnect from them before unloading.

## State Machine ##
The ControllerLoader uses a state machine to sequence loading and unloading subcontrollers. Here is a diagram of the state machine, followed by a description of each state transition (the work is done while transitioning between states, not while the ControllerLoader is in each state)).

![http://wiki.atrias.googlecode.com/git/CLStateMachine.png](http://wiki.atrias.googlecode.com/git/CLStateMachine.png)

Here are the triggers for and actions executed during the transitions:
| Transition number | Trigger                      | Actions                                                      |
|:------------------|:-----------------------------|:-------------------------------------------------------------|
| 1                 | GUI commands controller load | Load controller component; Tell RTOps to activate controller |
| 2                 | Receive ACK\_CM event         | Send response to GUI                                         |
| 3                 | GUI sends controller command | Tell RTOps to deactivate controller                          |
| 4                 | Receive ACK\_CM event         | Unload controller component                                  |

Transition #2 should occur whether or not RTOps was successful at connecting with the controller.