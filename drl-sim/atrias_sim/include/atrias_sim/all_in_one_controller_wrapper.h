// Devin Koepl

#ifndef ALL_IN_ONE_CONTROLLER_WRAPPER_HH
#define ALL_IN_ONE_CONTROLLER_WRAPPER_HH

#include <algorithm>
#include <assert.h>

#include <ros/ros.h>

// Custom Callback Queue
#include <ros/callback_queue.h>
#include <ros/advertise_options.h>

// Boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <gazebo/Sensor.hh>
#include <gazebo/Global.hh>
#include <gazebo/XMLConfig.hh>
#include <gazebo/Simulator.hh>
#include <gazebo/gazebo.h>
#include <gazebo/World.hh>
#include <gazebo/PhysicsEngine.hh>
#include <gazebo/GazeboError.hh>
#include <gazebo/ControllerFactory.hh>
#include <gazebo/Body.hh>
#include <gazebo/Pose3d.hh>
#include <gazebo/Controller.hh>
#include <gazebo/Param.hh>
#include <gazebo/Model.hh>
#include <gazebo/Quatern.hh>
#include <gazebo/Mass.hh>

#include <atrias/atrias_parameters.1.h>

#include <atrias_controllers/controller.h>
#include <atrias_sim/control_switcher_state_machine.h>

#include <atrias_controllers/atrias_srv.h>

#include <drl_library/drl_math.h>

namespace gazebo
{
/** \defgroup GazeboRosForce Plugin XML Reference and Example

  Example Usage:
  \verbatim
  <model:physical name="box_model">
    <body:empty name="box_body">
     ...
    </body:empty>
    <controller:gazebo_ros_force name="box_force_controller" plugin="libgazebo_ros_force.so">
        <alwaysOn>true</alwaysOn>
        <updateRate>15.0</updateRate>
        <bodyName>box_body</bodyName>
    </controller:gazebo_ros_force>
  </model:phyiscal>
  \endverbatim
 
\{
*/

class AllInOneControllerWrapper : public Controller
{
  /// \brief Constructor
  /// \param parent The parent entity, must be a Model or a Sensor
  public: AllInOneControllerWrapper(Entity *parent);

  /// \brief Destructor
  public: virtual ~AllInOneControllerWrapper();

  /// \brief Load the controller
  /// \param node XML config node
  protected: virtual void LoadChild(XMLConfigNode *node);

  /// \brief Update the controller
  protected: virtual void UpdateChild();
  protected: virtual void InitChild();
  protected: virtual void FiniChild();

  /// \brief A pointer to the parent entity
  private: Model *myParent;

  /// \brief A pointer to the Body
	private: Body *body;
  private: Body *motorA, *motorB;
	private: Body *legA, *legB;

  /// \brief A mutex to lock access to fields that are used in ROS message callbacks
  private: boost::mutex lock;

  /// \brief inputs
  private: ParamT<std::string> *bodyNameP; 
  private: std::string bodyName;

  private: ParamT<std::string> *motorANameP; 
  private: std::string motorAName;

  private: ParamT<std::string> *motorBNameP; 
  private: std::string motorBName;

  private: ParamT<std::string> *legANameP; 
  private: std::string legAName;

  private: ParamT<std::string> *legBNameP; 
  private: std::string legBName;

	private: ControllerInput *controller_input;
	private: ControllerOutput *controller_output;
	private: ControllerState *controller_state;
	private: ControllerData *controller_data;

	private: void generate_controller_input();

	// GUI Interface
	private: bool atrias_gui_callback(atrias_controllers::atrias_srv::Request&, atrias_controllers::atrias_srv::Response&);
	private: ros::NodeHandle *nh;
	private: ros::ServiceServer gui_srv;

  // Custom Callback Queue
  private: ros::CallbackQueue queue;
  private: boost::thread* callback_queuethread;
  private: void QueueThread();

	private: bool motors_enabled;
	private: int controller;
};

}
#endif

