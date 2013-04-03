#ifndef __ATC_SLIP_RUNNING_H__
#define __ATC_SLIP_RUNNING_H__

/*! \file controller_component.h
 *  \author Mikhail Jones
 *  \brief Orocos Component header for atc_slip_running controller.
 */

// Initialize ==================================================================
// Orocos ----------------------------------------------------------------------
#include <rtt/os/main.h>
#include <rtt/RTT.hpp>
#include <rtt/Logger.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/OperationCaller.hpp>
#include <rtt/Component.hpp>

// C ---------------------------------------------------------------------------
#include <stdlib.h>
#include <atrias_shared/GuiPublishTimer.h>
#include <atrias_shared/globals.h>
#include <robot_invariant_defs.h>

// Datatypes -------------------------------------------------------------------
#include <atc_slip_running/controller_input.h>
#include <atc_slip_running/controller_status.h>
#include <atc_slip_running/controller_log_data.h>
#include <atrias_msgs/robot_state.h>
#include <atrias_msgs/controller_output.h>
#include <atrias_shared/controller_structs.h>
#include <atrias_shared/atrias_parameters.h>

using namespace RTT;
using namespace Orocos;
using namespace atc_slip_running;

namespace atrias {
using namespace shared;
namespace controller {

// ATCSlipRunning ================================================================
class ATCSlipRunning : public TaskContext {

	private:	
		// Operations ----------------------------------------------------------
		// This Operation is called by the RT Operations Manager.
		atrias_msgs::controller_output runController(atrias_msgs::robot_state rs);
		atrias_msgs::controller_output co;
		void passiveStanceControl();
		void forceStanceControl();
		void egbFlightControl();

		// Logging
		controller_log_data              logData;
		OutputPort<controller_log_data>  logPort;

		// GUI
		shared::GuiPublishTimer                         *pubTimer;
		controller_input                                guiIn;
		controller_status                               guiOut;
		OutputPort<controller_status>                   guiDataOut;
		InputPort<controller_input>                     guiDataIn;
		
		// ASCCommonToolkit
		std::string ascCommonToolkit0Name;
		TaskContext *ascCommonToolkit0;
		OperationCaller<double(double, double)> legStiffness0;
		
		// Variables -----------------------------------------------------------
		
		

	public:
		// Constructor ---------------------------------------------------------
		ATCSlipRunning(std::string name);
		
		// Log controller data -------------------------------------------------
	    RTT::OperationCaller<std_msgs::Header(void)> getROSHeader;

		// Standard Orocos hooks -----------------------------------------------
		bool configureHook();
		bool startHook();
		void updateHook();
		void stopHook();
		void cleanupHook();
		
}; // class ATCSlipRunning

} // namespace controller
} // namespace atrias

#endif