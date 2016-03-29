# Coordinate System #
All coordinates utilized here are in the coordinate system utilized for ATRIAS's software system, unless stated otherwise.

# Leg Length <=> Angles #

## Coordinates used ##
l = leg length

θ = leg angle

a<sub>1</sub> = A leg segment angle

a<sub>2</sub> = B leg segment angle

## Angles to Length ##

l = cos((a<sub>2</sub> - a<sub>1</sub>) / 2)

## Length and Angle to segment Angles ##

a<sub>1</sub> = θ - arccos(l)

a<sub>2</sub> = θ + arccos(l)

# Leg length and Zero Deflection leg length => Force #

## Values used ##

k = Spring constant (Nm/rad)

l = leg length

d = zero deflection leg length

## Formula ##

force = 4·k·l·(cos<sup>-1</sup>(l) - cos<sup>-1</sup>(d))·csc(2·cos<sup>-1</sup>(l))

# Torque <=> Force Conversions #
This sections contains conversions between toe forces and spring torques.

## Assumptions ##
Relevant leg links have lengths of .5

## Coordinates used ##

F<sub>x</sub> = horizontal component of toe force, positive = robot pushing its CoM in the positive-X direction

F<sub>z</sub> = Z component of force, positive = robot fighting gravity

a<sub>1</sub> = A leg segment's angular position

a<sub>2</sub> = B leg segment's angular position

T<sub>1</sub> = A spring's torque

T<sub>2</sub> = B spring's torque

## Force to Torques ##

T<sub>1</sub> = (sin(a<sub>1</sub>) f<sub>x</sub> + cos(a<sub>1</sub>) f<sub>z</sub>) / 2

T<sub>2</sub> = (sin(a<sub>2</sub>) f<sub>x</sub> + cos(a<sub>2</sub>) f<sub>z</sub>) / 2

## Torques to Force ##

f<sub>x</sub> = 2 csc(a<sub>1</sub> - a<sub>2</sub>) (cos(a<sub>2</sub>) T<sub>1</sub> - cos(a<sub>1</sub>) T<sub>2</sub>)

f<sub>z</sub> = 2 csc(a<sub>1</sub> - a<sub>2</sub>) (-sin(a<sub>2</sub>) T<sub>1</sub> + sin(a<sub>1</sub>) T<sub>2</sub>)