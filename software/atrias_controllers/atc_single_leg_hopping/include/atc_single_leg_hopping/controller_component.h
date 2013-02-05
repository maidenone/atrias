#ifndef __ATC_SINGLE_LEG_HOPPING_H__
#define __ATC_SINGLE_LEG_HOPPING_H__

/*! \file controller_component.h
 *  \author Mikhail Jones
 *  \brief Orocos Component header for atc_single_leg_hopping controller.
 */

// Orocos 
#include <rtt/os/main.h>
#include <rtt/RTT.hpp>
#include <rtt/Logger.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/OperationCaller.hpp>
#include <rtt/Component.hpp>

// C
#include <stdlib.h>

#include <atrias_shared/GuiPublishTimer.h>
#include <atrias_shared/globals.h>
#include <robot_invariant_defs.h>

// Datatypes
#include <atc_single_leg_hopping/controller_input.h>
#include <atc_single_leg_hopping/controller_status.h>
#include <atc_single_leg_hopping/controller_log_data.h>
#include <atrias_msgs/robot_state.h>
#include <atrias_msgs/controller_output.h>
#include <atrias_shared/controller_structs.h>

using namespace RTT;
using namespace Orocos;
using namespace atc_single_leg_hopping;

namespace atrias {
using namespace shared;
namespace controller {

class ATCSingleLegHopping : public TaskContext {
private:
    // This Operation is called by the RT Operations Manager.
    atrias_msgs::controller_output runController(atrias_msgs::robot_state rs);
    atrias_msgs::controller_output co;

    // Logging
    controller_log_data              logData;
    OutputPort<controller_log_data>  logPort;

    // For the GUI
    shared::GuiPublishTimer                         *pubTimer;
    controller_input                                guiIn;
    controller_status                               guiOut;
    OutputPort<controller_status>                   guiDataOut;
    InputPort<controller_input>                     guiDataIn;

    // Variables for subcontrollers
    // Leg PD subcontroller
    std::string pd0Name;
    TaskContext *pd0;
    Property<double> P0;
    Property<double> D0;
    OperationCaller<double(double, double, double, double)> pd0Controller;

    // Hip PD subcontroller
    std::string pd1Name;
    TaskContext *pd1;
    Property<double> P1;
    Property<double> D1;
    OperationCaller<double(double, double, double, double)> pd1Controller;

    // Transforms
    OperationCaller<MotorAngle(double, double)> legToMotorPos;

    // Math variables
    double Fx, Fy, w, v0, g, l1, l2, k, J11, J12, J21, J22, tauA, tauB, desDeflA, desDeflB, deflA, deflB, legAng, legLen, delta; 
    double r, dr, q, dq;
    double rNew, drNew, qNew, dqNew;
    double leftHipAngle, rightHipAngle;
    MotorAngle leftMotorAngle;
    MotorAngle rightMotorAngle;

public:
    // Constructor
    ATCSingleLegHopping(std::string name);

    // Standard Orocos hooks
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
};
}
}

#endif
