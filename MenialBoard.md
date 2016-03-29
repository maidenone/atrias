# Introduction #

The menial board is an interface board used to easily connect inputs and outputs to the the medulla board. All the connectors on the menial board are Molex Sherlock connectors with the exception of the motor power and amplifier connectors. The menial board has the following connectors:

  * Limit Switch (8) - uses xMega internal pullup resistors
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/limit_sw.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/limit_sw.png)
  * SSI/BISS Encoder (3)
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/biss_ssi_encoder.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/biss_ssi_encoder.png)
  * Incremental Encoder (1) - Differential quadrature input with index
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/inc_encoder.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/inc_encoder.png)
  * Hall Effect Sensor (1) - Hall effect input for 3 phase brushless DC motor
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/hall_sensor.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/hall_sensor.png)
  * Thermistors (1) - Single input, supports three thermistors intended for use on motor, uses 4.7k pullup resistors.
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/thermistor.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/thermistor.png)
  * Auxiliary Analog or Digital input (3) - Connector has 3.3 volts, ground, and two inputs, one with a 4.7k pullup and one without
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/aux_input.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/aux_input.png)
  * LED (1) - Connector for RGB LED
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/LED_output.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/LED_output.png)
  * EStop in/out (2)
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/e_stop.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/e_stop.png)
  * Logic Power (1)
> > ![http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/voltage_input.png](http://atrias.googlecode.com/svn/trunk/hardware/menial_board_v2/Documentation/voltage_input.png)
  * Motor Power and Motor Output - This is a terminal block which has the 50V power input to the motor amplifier and the output from the motor driver to the motor.
  * AMC Amplifier Connector
> > ![http://i.imgur.com/33Dr70P.png](http://i.imgur.com/33Dr70P.png)
    * PWM and Direction - for controlling the motor
    * 3 digital input lines to the amp
    * 3 digital output lines from amp
    * RS232 communication to medulla
    * Hall effect input to amp from hall effect connector
    * Incremental encoder input to amp from connector