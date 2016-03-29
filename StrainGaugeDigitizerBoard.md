# Introduction #

The purpose of the strain gauge digitizer is to amplify and digitize the strain guage measurement before the signal goes through the motor and to the medulla. By amplifying and converting the analog output to a differential digital signal right at the knee there should hopefully be much less noise in the measurement.

![http://atrias.googlecode.com/svn/trunk/hardware/strain_gauge_digitizer_v1/strain_gauge_digitizer_dimensions.png](http://atrias.googlecode.com/svn/trunk/hardware/strain_gauge_digitizer_v1/strain_gauge_digitizer_dimensions.png)

# Details #
  * For amplification of the half Wheatstone bridge, we will use the TI (Burr-Brown) INA122 instrumentation amplifier.
  * The Texas Instruments ADS8331 ADC will be used for digitizing the amplified signal. It can also be used to digitize the signal from the toe force sensor.
  * The Texas Instruments SN65LVDS049 will be used as the differential line driver for communications with the medulla board.
  * The board will need to be small enough to fit inside the leg tube.

## Prototyping Results ##
I prototyped the circuit and learned a couple things.
  1. The LT1167 amplifier is _not_ a rail to rail amplifier. In order to get the most use out of our ADC, we should use a rail to rail amplifier.
  1. We need a trim pot on the fixed resistor of the Wheatstone bridge. Because we need to be able to account for inaccuracies in both the fixed resistors and the strain gauges.
  1. We will need a gain on the amplifier of somewhere in the order of 5000. With this gain I was able to get full scale output with a visually imperceptible deflection.


## Soldering Instructions ##
The ferrite bead used for noise filtering is sensitive to extreme heats and can be ruined if soldered using normal temperatures. In order to prevent damage to the bead, reflow using the instructions on page 4 of the [datasheet](http://product.tdk.com/en/catalog/datasheets/e9412_mmz.pdf).

### Pinout ###

![http://i.imgur.com/1bO8PDk.png](http://i.imgur.com/1bO8PDk.png)

What this picture shows is a top down view of the connector on the board and the sherlock connector should be built to match this.