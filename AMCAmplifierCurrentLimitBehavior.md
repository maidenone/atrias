# Introduction #

The firmware on the AMC amplifiers implements a proprietary current limiting algorithm that changes the current limit depending on the measured current draw, temperature, and time. AMC has documented the behavior of this algorithm to some extent [here](http://www.a-m-c.com/download/manual/AMC_DriveWareSoftwareManual.pdf). However, the behavior described in documentation is a simplified and more conservative description of what actually goes on. AMC was reluctant to elaborate on the algorithm beyond what is described in this document, so it was reverse-engineered from observations made using the DriveWare software.


# The Algorithm #

## Sample cases ##

You may find it tedious to use the current limiting algorithm itself on a daily basis, so here are some numbers that may provide you with an intuition:

  * **The maximum duty cycle of a square wave with peak current above 60 A is 33% (i.e., foldback for some time, then rest at zero current for twice as long).**
  * **To sustain a half-sine wave, the peak current must be 101.5 A or lower.**

## Detailed explanation ##

The current limit behavior is illustrated below. You may want to read the amplifier configuration section below if some of the terms used are unclear.

![![](http://wiki.atrias.googlecode.com/git/amc_current_limit_behavior.png)](http://wiki.atrias.googlecode.com/git/amc_current_limit_behavior_large.jpg)

The effective current limit is determined by a counter and the foldback period.

  * The counter: decrements according to the foldback rate (e.g., over A1) and increments at a rate in direct proportion to the target current. Its maximum value is greater than the peak current limit. This maximum value, in conjunction with the foldback period, determines the peak current period. Its minimum value equals the continuous current limit. The counter decrements whenever the commanded current exceeds the continuous current limit and increments otherwise. In addition, if the counter is decrementing, it must equal the effective current limit (i.e., if the counter is incrementing and exceeds the effective current limit, it will "snap" back to the effective current limit if it starts decrementing again for any amount of time, as illustrated in the junction between A2 and A3).
  * The foldback period: determines the rate at which the counter decrements, as well as the minimum recovery period. In the case that the counter increments faster than the negative of its foldback rate, the effective current limit is capped by this "reverse" foldback rate.


# Amplifier Configuration #

There are several configuration parameters for the amplifiers you should keep in mind:

  * **Continuous current limit**: the amplifier can drive a load continuously at this current without overheating beyond the safety temperature cutoff.
  * **Peak current limit**: the amplifier cannot supply more than this amount of current at any time.
  * **Peak current period**: if fully recovered, the amplifier can supply peak current for this duration before the active current limit decreases past the peak current limit.
  * **Foldback period**: the time it takes for the current limit to reach the continuous current limit (this excludes the peak current time).
  * **Temperature cutoff**: the amplifier disables if it reaches this temperature.
  * **Current limiting scheme**: the current limit can be set based on either: 1) simply how long the amplifier drives a load above the continuous current limit, or 2) for how long and by how much above the continuous current limit the load is driven. (Disclaimer: we have always used the time-based scheme, and I personally don't know the details of how the second scheme behaves.)

Each amplfier was configured by AMC to "their limits." The amplifiers on ATRIAS are currently configured as follows:

  * Continuous current limit: 30 A
  * Peak current limit: 60 A
  * Peak current time: 2 s
  * Foldback time: 10 s
  * Temperature cutoff: 90 deg C (TODO: verify)
  * Current limiting scheme: time-based

Note that with the double amplifier setup, the effective current limits are doubled.