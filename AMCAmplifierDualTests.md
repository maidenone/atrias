# Introduction #

Until March 2013, each motor on ATRIAS was powered by a single DZRALTE-060L080 AMC amplifier.

Problematically, the amplifiers scale down from their peak current limit of 60 A to the continuous current limit of 30 A very quickly during bipedal walking. Consequently, we saturate the amplifiers constantly.

This page documents the test procedures and results of using two amplifiers in parallel.

## Amplifier Configuration ##

Each amplfier was configured by AMC to "their limits."

Relevant configuration parameters are as follows:

  * Continuous current limit: 30 A
  * Peak current limit: 60 A
  * Peak current time: 2 s
  * Foldback time: 10 s
  * Temperature cutoff: TODO
  * Current limiting scheme: time-based

Running an amplifier at continuous current on a large block of aluminum brings its temperature to just below the safety cutoff.


# Parallel Amplifiers #

## Problem ##

Each motor in ATRIAS has two electrically isolated but magnetically coupled windings. When running two AMC amplifiers in parallel (configured in current control mode) on separate windings, there are large electrical oscillations and over-current shutdowns occur.

## Hypothesis ##

It was hypothesized that the control loops in the two amplifiers fought each other (and thereby failed) to achieve the same target current.

## Test Procedure ##

To test this, two amplifiers were set up in parallel on separate windings. One current probe was attached to one of the 3-phase outputs on each winding. The amplifiers were then commanded to do current control. The current measurements are shown in the figure below.

![http://wiki.atrias.googlecode.com/git/double_amp_current_control.png](http://wiki.atrias.googlecode.com/git/double_amp_current_control.png)

The test was then repeated with the amplifiers configured for velocity control. The current measurements are shown below.

![http://wiki.atrias.googlecode.com/git/double_amp_velocity_control.png](http://wiki.atrias.googlecode.com/git/double_amp_velocity_control.png)

## Solution ##

The six PWM control signal traces going from the DSP to the gate drivers on one of the AMC amplifiers was cut. The same signals from the other AMC amplifier was spliced into the gate drivers of the former AMC amplifier.

This allows us to run velocity control with twice the current capacity.

## Concerns ##

It is possible that the PWM dead time is controlled by the DSP and not by the gate drivers. If the dead time is very small and there is enough delay between amplifers, then shoot-through could occur.
