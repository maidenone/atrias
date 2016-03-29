# Boom #

## Pitch Encoder ##
Use the locked body method if the body's locked in place and the digital level is available. Use the level body method if the body is free. If the body is locked and the digital level is not available, an accurate calibration cannot be done (but you may obtain a less accurate one by treating the robot as level).

### Locked body method ###
Place the digital level against the front and back of the body; average the values to obtain the body's actual pitch. Simultaneously record the value recorded by the pitch encoder.

Then utilize the value PITCH\_ENCODER\_RAD\_PER\_TICK from robot\_invariant\_defs.h to calculate what the encoder should read when the robot is truly vertical. This is the value for BOOM\_PITCH\_VERTICAL\_VALUE in robot\_variant\_defs.h

### Level body method ###
Level the robot body. This may be done by shifting the CoM of the robot my moving the legs. Then record the pitch encoder's value.

## Z Encoder ##
This calibration should be done with the robot near the "center" of its vertical motion (i.e. the center of our coordinate system should be about 1 meter off the ground). This is to ensure the wraparound compensation operates correctly at startup.

Place the digital level on the boom arm. Record the angle of the boom arm as well as the encoder's reading. The encoder's reading goes into the BOOM\_Z\_CALIB\_VAL define.

To determine the boom angle for BOOM\_Z\_CALIB\_LOC, convert the digital level's angle to radians and subtract it from pi.

Alternatively, other methods may be utilized to determine the boom angle. One that works fairly well is to utilize a measuring tape and trigonometry to calculate the boom angle. This appears to be at least as accurate as the digital level.

## X Encoder ##
The X position is zero at startup and does not require calibration.

# Hip #

Near the center of the hip's rotation, there is a flat spot in the carbon fiber body. Utilize the digital level to compare the angle of this spot (body angle) with the angle of the outside of the leg (which is the hip angle) to determine the actual hip angle (convert to our coordinate system). Read off the value of the encoder.

The encoder's reading goes in LEFT/RIGHT\_HIP\_CALIB\_VAL and the hip's angle goes in LEFT/RIGHT\_HIP\_CALIB\_LOC

# Leg #

There are spots for pins on each side of every leg. Insert the pins -- this locks both the motor and the leg to 15 degrees off vertical. Read off the encoder value -- this encoder value is the calibration value.