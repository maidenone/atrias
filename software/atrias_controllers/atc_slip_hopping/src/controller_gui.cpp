/*! \file controller_gui.cpp
 *  \author Mikhail Jones
 */

#include <atc_slip_hopping/controller_gui.h>

//! \brief Initialize the GUI.
bool guiInit(Glib::RefPtr<Gtk::Builder> gui) {
	// Get widgets
	gui->get_widget("slip_spring_spinbutton", slip_spring_spinbutton);
	gui->get_widget("standing_leg_spinbutton", standing_leg_spinbutton);
	gui->get_widget("hop_height_spinbutton", hop_height_spinbutton);
	gui->get_widget("slip_leg_spinbutton", slip_leg_spinbutton);
	gui->get_widget("leg_pos_kp_spinbutton", leg_pos_kp_spinbutton);
	gui->get_widget("leg_for_kp_spinbutton", leg_for_kp_spinbutton);
	gui->get_widget("leg_for_kd_spinbutton", leg_for_kd_spinbutton);
	gui->get_widget("leg_pos_kd_spinbutton", leg_pos_kd_spinbutton);
	gui->get_widget("hip_pos_kp_spinbutton", hip_pos_kp_spinbutton);
	gui->get_widget("hip_pos_kd_spinbutton", hip_pos_kd_spinbutton);
	gui->get_widget("main_controller_combobox", main_controller_combobox);
	gui->get_widget("spring_type_combobox", spring_type_combobox);
	gui->get_widget("force_type_combobox", force_type_combobox);
	gui->get_widget("stance_controller_combobox", stance_controller_combobox);
	gui->get_widget("hop_type_combobox", hop_type_combobox);
	
	gui->get_widget("force_threshold_td_spinbutton", force_threshold_td_spinbutton);
	gui->get_widget("force_threshold_to_spinbutton", force_threshold_to_spinbutton);
	gui->get_widget("position_threshold_td_spinbutton", position_threshold_td_spinbutton);
	gui->get_widget("left_toe_pos_spinbutton", left_toe_pos_spinbutton);
	gui->get_widget("right_toe_pos_spinbutton", right_toe_pos_spinbutton);
	gui->get_widget("hopping_state_spinbutton", hopping_state_spinbutton);

	// Set ranges
	slip_spring_spinbutton->set_range(0.0, 50000.0);
	standing_leg_spinbutton->set_range(0.5, 0.95);
	hop_height_spinbutton->set_range(0.0, 0.25);
	slip_leg_spinbutton->set_range(0.5, 0.95);
	leg_pos_kp_spinbutton->set_range(0.0, 7500.0);
	leg_for_kp_spinbutton->set_range(0.0, 7500.0);
	leg_for_kd_spinbutton->set_range(0.0, 500.0);
	leg_pos_kd_spinbutton->set_range(0.0, 500.0);
	hip_pos_kp_spinbutton->set_range(0.0, 500.0);
	hip_pos_kd_spinbutton->set_range(0.0, 50.0);
	
	force_threshold_td_spinbutton->set_range(-100.0, 100.0);
	force_threshold_to_spinbutton->set_range(-100.0, 100.0);
	position_threshold_td_spinbutton->set_range(0.0, 0.05);
	left_toe_pos_spinbutton->set_range(2.1, 2.5);
	right_toe_pos_spinbutton->set_range(2.1, 2.5);
	hopping_state_spinbutton->set_range(0, 1);

	// Set increments
	slip_spring_spinbutton->set_increments(100.0, 0.0);
	standing_leg_spinbutton->set_increments(0.01, 0.0);
	hop_height_spinbutton->set_increments(0.01, 0.0);
	slip_leg_spinbutton->set_increments(0.01, 0.0);
	leg_pos_kp_spinbutton->set_increments(10.0, 0.0);
	leg_for_kp_spinbutton->set_increments(10.0, 0.0);
	leg_for_kd_spinbutton->set_increments(1.0, 0.0);
	leg_pos_kd_spinbutton->set_increments(1.0, 0.0);
	hip_pos_kp_spinbutton->set_increments(10.0, 0.0);
	hip_pos_kd_spinbutton->set_increments(1.0, 0.0);
	
	force_threshold_td_spinbutton->set_increments(1.0, 0.0);
	force_threshold_to_spinbutton->set_increments(1.0, 0.0);
	position_threshold_td_spinbutton->set_increments(0.001, 0.0);
	left_toe_pos_spinbutton->set_increments(0.01, 0.0);
	right_toe_pos_spinbutton->set_increments(0.01, 0.0);
	hopping_state_spinbutton->set_increments(1, 0);

	// Set values
	slip_spring_spinbutton->set_value(28000.0);
	standing_leg_spinbutton->set_value(0.90);
	hop_height_spinbutton->set_value(0.05);
	slip_leg_spinbutton->set_value(0.85);
	leg_pos_kp_spinbutton->set_value(200.0);
	leg_for_kp_spinbutton->set_value(100.0);
	leg_for_kd_spinbutton->set_value(2.0);
	leg_pos_kd_spinbutton->set_value(20.0);
	hip_pos_kp_spinbutton->set_value(150.0);
	hip_pos_kd_spinbutton->set_value(10.0);
	
	force_threshold_td_spinbutton->set_value(50.0);
	force_threshold_to_spinbutton->set_value(30.0);
	position_threshold_td_spinbutton->set_value(0.02);
	left_toe_pos_spinbutton->set_value(2.20);
	right_toe_pos_spinbutton->set_value(2.45);
	hopping_state_spinbutton->set_value(0);

	// Set up subscriber and publisher.
	sub = nh.subscribe("ATCSlipHopping_status", 0, controllerCallback);
	pub = nh.advertise<atc_slip_hopping::controller_input>("ATCSlipHopping_input", 0);
	return true;
}


void controllerCallback(const atc_slip_hopping::controller_status &status) {
	controllerDataIn = status;
}

//! \brief Get parameters from the server and configure GUI accordingly.
void getParameters() {
	// Get parameters in the atrias_gui namespace
	nh.getParam("/atrias_gui/slip_spring", controllerDataOut.slip_spring);
	nh.getParam("/atrias_gui/standing_leg", controllerDataOut.standing_leg);
	nh.getParam("/atrias_gui/hop_height", controllerDataOut.hop_height);
	nh.getParam("/atrias_gui/slip_leg", controllerDataOut.slip_leg);
	nh.getParam("/atrias_gui/leg_pos_kp", controllerDataOut.leg_pos_kp);
	nh.getParam("/atrias_gui/leg_for_kp", controllerDataOut.leg_for_kp);
	nh.getParam("/atrias_gui/leg_for_kd", controllerDataOut.leg_for_kd);
	nh.getParam("/atrias_gui/leg_pos_kd", controllerDataOut.leg_pos_kd);
	nh.getParam("/atrias_gui/hip_pos_kp", controllerDataOut.hip_pos_kp);
	nh.getParam("/atrias_gui/hip_pos_kd", controllerDataOut.hip_pos_kd);
	int main_controller;
	nh.getParam("/atrias_gui/main_controller", main_controller);
	controllerDataOut.main_controller = (uint8_t)main_controller;
	int spring_type;
	nh.getParam("/atrias_gui/spring_type", spring_type);
	controllerDataOut.spring_type = (uint8_t)spring_type;
	int force_type;
	nh.getParam("/atrias_gui/force_type", force_type);
	controllerDataOut.force_type = (uint8_t)force_type;
	int stance_controller;
	nh.getParam("/atrias_gui/stance_controller", stance_controller);
	controllerDataOut.stance_controller = (uint8_t)stance_controller;
	int hop_type;
	nh.getParam("/atrias_gui/hop_type", hop_type);
	controllerDataOut.hop_type = (uint8_t)hop_type;
	
	nh.getParam("/atrias_gui/force_threshold_td", controllerDataOut.force_threshold_td);
	nh.getParam("/atrias_gui/force_threshold_to", controllerDataOut.force_threshold_to);
	nh.getParam("/atrias_gui/position_threshold_td", controllerDataOut.position_threshold_td);
	nh.getParam("/atrias_gui/left_toe_pos", controllerDataOut.left_toe_pos);
	nh.getParam("/atrias_gui/right_toe_pos", controllerDataOut.right_toe_pos);

	// Configure the GUI
	slip_spring_spinbutton->set_value(controllerDataOut.slip_spring);
	standing_leg_spinbutton->set_value(controllerDataOut.standing_leg);
	hop_height_spinbutton->set_value(controllerDataOut.hop_height);
	slip_leg_spinbutton->set_value(controllerDataOut.slip_leg);
	leg_pos_kp_spinbutton->set_value(controllerDataOut.leg_pos_kp);
	leg_for_kp_spinbutton->set_value(controllerDataOut.leg_for_kp);
	leg_for_kd_spinbutton->set_value(controllerDataOut.leg_for_kd);
	leg_pos_kd_spinbutton->set_value(controllerDataOut.leg_pos_kd);
	hip_pos_kp_spinbutton->set_value(controllerDataOut.hip_pos_kp);
	hip_pos_kd_spinbutton->set_value(controllerDataOut.hip_pos_kd);
	main_controller_combobox->set_active(controllerDataOut.main_controller);
	spring_type_combobox->set_active(controllerDataOut.spring_type);
	force_type_combobox->set_active(controllerDataOut.force_type);
	stance_controller_combobox->set_active(controllerDataOut.stance_controller);
	hop_type_combobox->set_active(controllerDataOut.hop_type);
	
	force_threshold_td_spinbutton->set_value(controllerDataOut.force_threshold_td);
	force_threshold_to_spinbutton->set_value(controllerDataOut.force_threshold_to);
	position_threshold_td_spinbutton->set_value(controllerDataOut.position_threshold_td);
	left_toe_pos_spinbutton->set_value(controllerDataOut.left_toe_pos);
	right_toe_pos_spinbutton->set_value(controllerDataOut.right_toe_pos);
}

//! \brief Set parameters on server according to current GUI settings.
void setParameters() {
	nh.setParam("/atrias_gui/slip_spring", controllerDataOut.slip_spring);
	nh.setParam("/atrias_gui/standing_leg", controllerDataOut.standing_leg);
	nh.setParam("/atrias_gui/hop_height", controllerDataOut.hop_height);
	nh.setParam("/atrias_gui/slip_leg", controllerDataOut.slip_leg);
	nh.setParam("/atrias_gui/leg_pos_kp", controllerDataOut.leg_pos_kp);
	nh.setParam("/atrias_gui/leg_for_kp", controllerDataOut.leg_for_kp);
	nh.setParam("/atrias_gui/leg_for_kd", controllerDataOut.leg_for_kd);
	nh.setParam("/atrias_gui/leg_pos_kd", controllerDataOut.leg_pos_kd);
	nh.setParam("/atrias_gui/hip_pos_kp", controllerDataOut.hip_pos_kp);
	nh.setParam("/atrias_gui/hip_pos_kd", controllerDataOut.hip_pos_kd);
	nh.setParam("/atrias_gui/main_controller", controllerDataOut.main_controller);
	nh.setParam("/atrias_gui/spring_type", controllerDataOut.spring_type);
	nh.setParam("/atrias_gui/force_type", controllerDataOut.force_type);
	nh.setParam("/atrias_gui/stance_controller", controllerDataOut.stance_controller);
	nh.setParam("/atrias_gui/hop_type", controllerDataOut.hop_type);
	
	nh.setParam("/atrias_gui/force_threshold_td", controllerDataOut.force_threshold_td);
	nh.setParam("/atrias_gui/force_threshold_to", controllerDataOut.force_threshold_to);
	nh.setParam("/atrias_gui/position_threshold_td", controllerDataOut.position_threshold_td);
	nh.setParam("/atrias_gui/left_toe_pos", controllerDataOut.left_toe_pos);
	nh.setParam("/atrias_gui/right_toe_pos", controllerDataOut.right_toe_pos);
}

//! \brief Update the GUI.
void guiUpdate() {
	// Set GUI values from controllerDataOut
	hopping_state_spinbutton->set_value(controllerDataIn.hopping_state);

	// Set values in controllerDataOut variable here
	controllerDataOut.slip_spring = slip_spring_spinbutton->get_value();
	controllerDataOut.standing_leg = standing_leg_spinbutton->get_value();
	controllerDataOut.hop_height = hop_height_spinbutton->get_value();
	controllerDataOut.slip_leg = slip_leg_spinbutton->get_value();
	controllerDataOut.leg_pos_kp = leg_pos_kp_spinbutton->get_value();
	controllerDataOut.leg_for_kp = leg_for_kp_spinbutton->get_value();
	controllerDataOut.leg_for_kd = leg_for_kd_spinbutton->get_value();
	controllerDataOut.leg_pos_kd = leg_pos_kd_spinbutton->get_value();
	controllerDataOut.hip_pos_kp = hip_pos_kp_spinbutton->get_value();
	controllerDataOut.hip_pos_kd = hip_pos_kd_spinbutton->get_value();
	controllerDataOut.main_controller = (uint8_t)main_controller_combobox->get_active_row_number();
	controllerDataOut.spring_type = (uint8_t)spring_type_combobox->get_active_row_number();
	controllerDataOut.force_type = (uint8_t)force_type_combobox->get_active_row_number();
	controllerDataOut.stance_controller = (uint8_t)stance_controller_combobox->get_active_row_number();
	controllerDataOut.hop_type = (uint8_t)hop_type_combobox->get_active_row_number();
	
	controllerDataOut.force_threshold_td = force_threshold_td_spinbutton->get_value();
	controllerDataOut.force_threshold_to = force_threshold_to_spinbutton->get_value();
	controllerDataOut.position_threshold_td = position_threshold_td_spinbutton->get_value();
	controllerDataOut.left_toe_pos = left_toe_pos_spinbutton->get_value();
	controllerDataOut.right_toe_pos = right_toe_pos_spinbutton->get_value();

	// Publish
	pub.publish(controllerDataOut);
}

//! \brief Take down the GUI.
void guiTakedown() {
}
