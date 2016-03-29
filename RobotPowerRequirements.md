# Calculated Power Requirements #

| **Idle (Motors Off)** | 43 watts |
|:----------------------|:---------|
| **Raibert Controller (thrashing)** | 375 watts |
| **Raibert Controller (hopping)** | 385 watts |


# Procedure #

To measure the power consumption of the robot, several different values must be determined.

### Measuring the capacitor bank capacity ###
Before we started, we measured the total capacitance of the capacitor bank. We did this by measuring how long it takes to drain the capacitors a certain percentage through a resistor of a known resistance. This allowed us to calculate the capacitance, as the capacitance, resistance of the resistor, and the amount of time the capacitors take to drain are related.

This is represented by the equation F=τ/r where F is the capacitance of the bank in farads, τ is the number of seconds it takes for the resistor to bring the capacitor voltage down to 36.8% of its charged value, and r is the resistance of the resistor.

The resistor was measured with a multimeter to have a resistance of 15.1Ω. The capacitor bank was charged to a starting voltage of 48 volts, and took 109 seconds to discharge to 36.8% of that, 17.7 volts.

Using the aforementioned equation, this indicates a capacitance value of 109/15.1≈7.2 farads. We could then move on to measuring the capacitor depletion of powering the robot.

### Measuring the average power required for a task ###
It was then possible to measure the amount of power used for a task. To do this, we fully charged the capacitor bank. Then we disconnected the charger and prepared the robot to run the task. As we started the controller, we measured the voltage of the capacitor bank and started a stopwatch. When the task was completed or the capacitor bank ran too low to properly continue the task, we stopped the stopwatch and again measured the voltage.

To calculate the energy consumption in watts we used this formula: F(A<sup>2-B</sup>2)/(s), where A is the voltage at the start of the task, B is the voltage at the end of the task, F is the capacitance of the capacitor bank in farads (7.2 in our case), and s is the length of time of the task in seconds.


# Measurements of individual tasks #

In this section we document the calculations done to find the power consumption during particular tasks.

###  ###
