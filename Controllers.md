# Controller Input and Output #
The robot state input struct (An example value: rs.lLeg.hip.legBodyAngle)
```
lLeg   (Note: there is also a rLeg with an identical structure)
  hip
    legBodyAngle
    legBodyVelocity
  halfA
    legAngle
    legVelocity
    motorAngle
    motorVelocity
    rotorAngle
    rotorVelocity
  halfB
    legAngle
    legVelocity
    motorAngle
    motorVelocity
    rotorAngle
    rotorVelocity
  toeSwitch
  kneeForce

position
  xPosition
  yPosition
  zPosition
  xVelocity
  yVelocity
  zVelocity
  boomAngle
  bodyPitch
  bodyPitchVelocity
```

The controller output struct (An example value: co.lLeg.motorCurrentA)
```
lLeg
  motorCurrentA
  motorCurrentB
  motorCurrentHip

rLeg
  motorCurrentA
  motorCurrentB
  motorCurrentHip
```

# Top-Level controllers #

## Hip Force Test ##
This controllers is for testing the Hip Force subcontroller as well as toe decoding. It will be rewritten for the new system once all the necessary subcontrollers have been ported/written.

## Equilibrium Point Control ##

Walking controller based on kinematic constraints, i.e. desired leg angle positions depending on gait phase. A hip controller is included to minimize joint stress by compensating for radius changes during leg swing.

This will be ported to the new controller system. When this is done, it should be switched to use the asc\_hip\_boom\_kinematics subcontroller, so we can remove the asc\_hip\_walking subcontroller. (This needs confirmation from Daniel).

# Subcontrollers #

## Force Deflection ##
This subcontroller is legacy -- do not use it. It will be removed as soon as all reverse dependencies are cleaned up.

## Hip Force ##
This subcontroller takes care of the hip on one side of the robot. It holds it vertical during flight and does knee force control during stance. It automatically switches between flight and stance based on the toe's force sensor.

It should not require any gain setting -- however, properties are available if you wish to set the gains yourself anyway.

It also has an operation that returns whether or not the leg is touching the ground. This operation must be run after the runController operation.

## asc\_coordinate\_transforms ##
### Service: ComToLegTransforms ###

**Operation: transforms**

What it does: Points the legs to two positions on the ground.

Assumptions/Notes:
  * The right leg points to x=0
  * The left leg points to x=stepLength
  * -stepLength < x < stepLength
  * No sanity checking done on returned leg lengths
Input:
  * Center of mass position and velocity (x, z, dx, dz)
  * Step length (stepLength)
Returns: A DesiredRobotState struct (positions and velocities of the legs). Check atrias\_shared/include/atrias\_shared/controller\_structs.h for details.

### Service: legToMotorTransforms ###

**Operation: posTransform**

What it does: Given a leg angle and length, returns motor angles

Assumptions/Notes:
  * No sanity checking is performed
  * Check atrias\_shared/include/atrias\_shared/controller\_structs.h for struct details.
Input:
  * leg angle
  * leg length
Returns:
  * Motor A and B positions (MotorAngle struct)

**Operation: velTransform**

What it does: Given a leg angle and length, returns motor velocities

Assumptions/Notes:
  * No sanity checking is performed
  * Check atrias\_shared/include/atrias\_shared/controller\_structs.h for struct details.
Input:
  * leg angle position and velocity
  * leg length position and velocity
Returns:
  * Motor A and B velocities (MotorVelocity struct)