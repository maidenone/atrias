# Introduction #

Since subcontrollers do not need to be Orocos components, and writing Orocos components
can be monotonous (not to mention verbose -- this dilutes the controller code), we will be
implementing a library to wrap controllers to make them easier to write.

# Adding Subcontrollers #

To add a subcontroller to a controller, follow these steps:
  * Add the subcontroller as a dependency is the manifest.xml
  * Include the subcontroller's class .hpp file in your controller's .hpp file.
  * Add one or more instances of the subcontroller as private members of your controller's class.
  * Call the constructor for each instance of your subcontroller in the .cpp file

# Steps for Converting #

There are several steps to converting an "old-style" controller to the new style. Here are the steps in order (the example controller here is asc\_hip\_force):
  1. Come up with a new controller name -- this should be the name of a class (like ASCHipForce, not asc\_hip\_force).
  1. Make a new .hpp file in the include directory (next to the existing controller\_component.h file), and copy over asc\_pd's (or atc\_motor\_position's if it's a top-level controller) .hpp file into a file with the new name.
  1. Do the same inside the src/ directory for the .cpp files.
  1. Edit both the header and .cpp files -- change all references to ASCPD to references to your controller's name
  1. Copy over all the controller's functionality. Replace old-style logging with new-style logging.
  1. Find the following lines in the CMakeLists.txt:
```
     orocos_component(asc_hip_force src/controller_component.cpp)
     ros_generate_rtt_typekit(asc_hip_force)
     target_link_libraries(asc_hip_force ASCLoader-${OROCOS_TARGET})
```
> If this is a subcontroller, add the following lines:
```
     orocos_library(<CONTROLLER_NAME> src/<CONTROLLER_NAME>.cpp)
     target_link_libraries(<CONTROLLER_NAME> ControlLib-${OROCOS_TARGET})
```
> If this is a top-level controller, instead add the following lines:
```
     orocos_component(<CONTROLLER_NAME> src/<CONTROLLER_NAME>.cpp)
     target_link_libraries(<CONTROLLER_NAME> ControlLib-${OROCOS_TARGET})
```
> Then (regardless of the type of this controller), for each subcontroller this controller uses
```
     target_link_libraries(<CONTROLLER_NAME> <SUBCONTROLLER_NAME>-${OROCOS_TARGET})
```
  1. If this is a top-level controller, replace the start script with the one from atc\_motor\_position, then change the references to ATCMP to references to your controller.
  1. Do the same for the stop script.
  1. In the manifest.xml file, change the reference to "roscpp" to one to "atrias\_control\_lib"
  1. Make sure that all controller\_log\_data and controller\_status ROS messages have the following member:
```
Header header
```

# Examples #

Here are some code samples of a top-level controller and a subcontroller written via the planned library:

# Subcontroller #

Here is a sample PD subcontroller:

Header file, ASCPD.hpp:
```
#ifndef ASCPD_HPP
#define ASCPD_HPP
 
/**
  * @file ASCPD.hpp
  * @author Ryan Van Why
  * @brief This implements a simple PD controller.
  */

// The include for the controller class
#include <atrias_control_lib/AtriasController.hpp>
// And for the logging helper class
#include <atrias_control_lib/LogPort.hpp>

// Our log data
#include "asc_pd/controller_log_data.h"

// Namespaces we're using
using namespace std;

// Our namespaces
namespace atrias {
namespace controller {

// The subcontroller class itself
class ASCPD : public AtriasController {
	public:
		/**
		  * @brief The constructor for this subcontroller
		  * @param parent The instantiating, "parent" controller.
		  * @param name   The name for this controller (such as "pdLeftA")
		  */
		ASCPD(AtriasController *parent, string name);

		/**
		  * @brief The main function for this controller.
		  * @param desPos The desired process value
		  * @param curPos The current process value
		  * @param desVel The desired rate of change in process value
		  * @param curVel The current rate of change of process value
		  * @return A commanded output.
		  *
		  * We're overloading this operator to make this class a functor. This makes
		  * calling this controller more convenient.
		  */
		double operator()(double desPos, double curPos, double desVel, double curVel);

		/**
		  * @brief Our P gain.
		  */
		double P;

		/**
		  * @brief Our D gain.
		  */
		double D;
	
	private:
		/** 
		  * @brief This is our logging port.
		  * You may have as many of these as you'd like of various types.
		  */
		LogPort<asc_pd::controller_log_data> log_out;
};

// End namespaces
}
}

#endif // ASCPD_HPP
```

Controller file, ASCPD.cpp:
```
#include "asc_pd/ASCPD.hpp"

// Again, we need to put our code inside the appropriate namespaces.
namespace atrias {
namespace controller {

/* Breakdown of the next few lines:
 * We need to call our parent class's constructor,
 * then we can call the LogPort's constructor. The second parameter
 * is the name for this log port, which controls how it appears in the
 * bagfiles.
 */
ASCPD::ASCPD(AtriasController *parent, string name) :
	AtriasController(parent, name),
	log_out(this, "log")
{
	// Initialize our gains to something safe.
	P = 0.0;
	D = 0.0;
}

double ASCPD::operator()(double desPos, double curPos, double desVel, double curVel) {
	/* Log our input data
	 * Suppose that the controller_log_data message is defined to have the
	 * following members:
	 *    float64 desPos
	 *    float64 curPos
	 *    float64 desVel
	 *    float64 curVel
	 *    float64 output
	 */
	log_out.data.desPos = desPos;
	log_out.data.desPos = desPos;
	log_out.data.desPos = desPos;
	log_out.data.desPos = desPos;

	// Compute the actual output command
	// I'm just placing this right in the log data for convenience.
	log_out.data.output = P * (desPos - curPos) + D * (desVel - curVel);

	// Transmit the log data
	log_out.send();

	// Return our output command -- sending the log data does not change
	// this value.
	return log_out.data.output;
}

}
}
```

# Top-Level Controller #

Here is a sample motor position controller utilizing the above PD controller:

Header file, ATCMP.hpp
```
#ifndef ATCMP_HPP
#define ATCMP_HPP

/**
  * @file ATCMP.hpp
  * @author Ryan Van Why
  * @brief This implements motor position control for 2 motors
  */

// Include the ATC class
#include <atrias_lib_control/ATC.hpp>
// No logging helper is needed -- one log port is automatically produced.

// Our logging data type.
#include "atc_motor_position/controller_log_data.h"
// The type transmitted from the GUI to the controller
#include "atc_motor_position/gui_to_controller.h"
// The type transmitted from the controller to the GUI
#include "atc_motor_position/controller_to_gui.h"

// Namespaces we're using
using namespace std;
using namespace atrias_msgs;

// Our namespaces
namespace atrias {
namespace controller {

/* Our class definition. We subclass ATC for a top-level controller.
 * If we don't need a data type (such as the controller-to-gui message),
 * we simply leave that spot in the template blank. The following example
 * shows the necessary definition if this controller were not to transmit
 * data to the GUI:
 *     class ATCMP : public ATC<log_data, gui_to_controller,>
 */
class ATCMP : public ATC<controller_log_data, gui_to_controller, controller_to_gui> {
	public:
		/**
		  * @brief The constructor for this controller.
		  * @param name The name of this component.
		  * Every top-level controller will have this name parameter,
		  * just like current controllers.
		  */
		ATCMP(string name);
	
	private:
		/**
		  * @brief This is the main function for the top-level controller.
		  * The ATC class automatically handles startup and shutdown,
		  * if they are not disabled.
		  */
		void controller();

		// PD controller for motor A
		ASCPD pdA;
		// PD controller for motor B
		ASCPD pdB;
};

}
}

#endif // ATCMP_HPP
```

Controller code file: ATCMP.cpp
```
#include "atc_motor_position/ATCMP.hpp"

// The namespaces this controller resides in
namespace atrias {
namespace controller {

// This constructor call is much simpler.
ATCMP::ATCMP(string name) :
	ATC(name)
{
	// We don't need to do much here, just call the ATC() constructor above.
}

void ATCMP::controller() {
	// The robot state is in an inherited member variable named rs
	// The controller output should be put in the inherited member co

	/* Here, we'll assume controller_log_data has the following members:
	 *     float64 desPosA
	 *     float64 desPosB
	 *     float64 P
	 *     float64 D
	 *     float64 outA
	 *     float64 outB
	 * The logOut class is an inherited member from ATC, and is of type
	 * controller_log_data. guiIn, similarly, is of type
	 * gui_to_controller
	 */
	logOut.desPosA = guiIn.desPosA;
	logOut.desPosB = guiIn.desPosB;
	logOut.P       = guiIn.P;
	logOut.D       = guiIn.D;

	// Command the outputs (and copy to our logging data).
	// This is where the definition of ASCPD as a functor is convenient.
	logOut.outA = co.lLeg.motorCurrentA =
		pdA(guiIn.desPosA, rs.lLeg.halfA.rotorAngle, 0, rs.lLeg.halfA.rotorVelocity);
	logOut.outB = co.lLeg.motorCurrentB =
		pdB(guiIn.desPosB, rs.lLeg.halfB.rotorAngle, 0, rs.lLeg.halfB.rotorVelocity);

	/* Copy over positions to the GUI output data
	 * Suppose that the guiOut message has the following members:
	 *     float64 posA
	 *     float64 posB
	 */
	guiOut.posA = rs.lLeg.halfA.rotorAngle;
	guiOut.posB = rs.lLeg.halfB.rotorAngle;

	/* Additionally, the following functions are available to command the robot state:
	 * commandHalt();    // Trigger a Halt
	 * commandEStop();   // Trigger an EStop
	 * commandDisable(); // Disable the robot
	 * setStartupEnabled(true/false) // Enable or disable the default startup controller
	 * setShutdownEnabled(true/false) // Enable or disable the shutdown controller
	 */
}

// We need to make top-level controllers components
ORO_CREATE_COMPONENT(ATCMP);

}
}
```

<a href='Hidden comment: 
vim: syntax=off
'></a>