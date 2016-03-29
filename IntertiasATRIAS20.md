All information is pulled from the Solidworks model. This model does not include the following.
  * Electrical wires &  wire management
  * Heat sink foam
  * Epoxy (carbon fiber tube to aluminum)
  * Loctite (all fasteners and for bearing press fits)

Please note that the axes shown in pictures are:

| Red   | +X |
|:------|:---|
| Green | +Y |
| Blue  | +Z |

The pinkish axes shown in pictures is the location of the center of mass. Both axis follow the Right Hand Rule.


---



---


# ATRIAS 2.0 Measurements #

## ATRIAS 2.0 Sub-Assembly Breakdown ##

### Biped ###

![http://img819.imageshack.us/img819/4169/bipedcomponentsforatria.png](http://img819.imageshack.us/img819/4169/bipedcomponentsforatria.png)

The Biped consists of one Torso and Two Legs. The Torso contains two Hip Motor Rotors.

### Leg ###

![http://img847.imageshack.us/img847/1361/labeledatrias2.png](http://img847.imageshack.us/img847/1361/labeledatrias2.png)

Components of the Leg:
| **ATRIAS 2.0 Leg** | **Sub-Assembly** | **Sub-Sub-Assembly** |
|:-------------------|:-----------------|:---------------------|
| Leg                | 1x Leg Drive     | 2x Leg Drive Rotor   |
|                    | 2x Drive Spring  |                      |
|                    | 1x Thigh Bone    |                      |
|                    | 1x Shin Bone     |                      |
|                    | 1x Fourbar Linkage |                      |
|                    | 1x Lower Leg     |                      |


---


## Basic Information Table ##
| **Part** | **Mass ea. (kg)** | **Distance Between Pin Joints (m)** |
|:---------|:------------------|:------------------------------------|
| **Biped**  | 59.59             | N/A                                 |
| **Leg**  | 21.48             | N/A                                 |
| **Torso** (Including 2x Hip Drive Rotor) | 16.67             | N/A                                 |
| Leg Drive (NOT 2x including Rotors) | 11.61             | N/A                                 |
| Leg Drive Rotor | 1.272             | N/A                                 |
| Drive Spring | 2.2937            | N/A                                 |
| Thigh Bone | 0.743185          | 0.5075                              |
| Shin Bone | 0.7515            | 0.3527                              |
| Four-bar Linkage | 0.1661            | 0.5000                              |
| Lower Leg | 0.2342            | 0.519                               |
| Hip Drive Rotor | 3.137             | N/A                                 |


---



---


## Inertial Info ##

### One whole Leg ###

![http://img5.imageshack.us/img5/5872/legforatriaswiki.png](http://img5.imageshack.us/img5/5872/legforatriaswiki.png)

Note: the inertia info provided for 'one whole leg' corresponds to the blue shaded portion in the robot picture above. This body rotates about the Z-axis (shown in picture but hard to read)

Mass = 21.48285668 kilograms

Center of mass: ( meters )
| X = 0.15699680 |
|:---------------|
| Y = -0.03205624 |
| Z = -0.00092478 |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.45452151 | Lxy = -0.00286138 | Lxz = 0.00262687 |
|:-----------------|:------------------|:-----------------|
| Lyx = -0.00286138 | Lyy = 0.19907772  | Lyz = 0.00888237 |
| Lzx = 0.00262687 | Lzy = 0.00888237  | Lzz = 0.39747541 |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.47661572 | Ixy = -0.11097872 | Ixz = -0.00049218 |
|:-----------------|:------------------|:------------------|
| Iyx = -0.11097872 | Iyy = 0.72860543  | Iyz = 0.00951923  |
| Izx = -0.00049218 | Izy = 0.00951923  | Izz = 0.94906058  |


---


### Leg Drive ###

![http://img804.imageshack.us/img804/4393/drive.png](http://img804.imageshack.us/img804/4393/drive.png)

Note: The Leg Drive assembly date below does not include the two Leg Drive Motor Rotor sub assembly's. This is provided elsewhere on this page.

Solidworks File name: DriveAssembly ( Assembly Configuration - LeftHip )

Mass = 11.61 kilograms (NOT including both leg motor rotor assemblies)

Center of mass: ( meters )
| X = -0.00002554 |
|:----------------|
| Y = 0.00245240  |
| Z = 0.00042748  |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.08327877 | Lxy = 0.01008097 | Lxz = 0.00446379 |
|:-----------------|:-----------------|:-----------------|
| Lyx = 0.01008097 | Lyy = 0.07835265 | Lyz = 0.00186696 |
| Lzx = 0.00446379 | Lzy = 0.00186696 | Lzz = 0.09318175 |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.08335074 | Ixy = 0.01008024 | Ixz = 0.00446366 |
|:-----------------|:-----------------|:-----------------|
| Iyx = 0.01008024 | Iyy = 0.07835478 | Iyz = 0.00187914 |
| Izx = 0.00446366 | Izy = 0.00187914 | Izz = 0.09325160 |


---


### Leg Drive Motor Rotor ###

![http://img256.imageshack.us/img256/8581/rotor.png](http://img256.imageshack.us/img256/8581/rotor.png)

On the robot, two of these assemblies are located in one Leg Drive Assembly. Rotation occurs about the Z axis (shown in picture but hard to read)

Solidworks File name: RotorAssembly ( Assembly Configuration - Default )

Mass = 1.27264096 kilograms

Center of mass: ( meters )
| X = 0.00000000 |
|:---------------|
| Y = 0.00000000 |
| Z = 0.00104909 |

Moments of inertia: ( kilograms x square meters ) Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.00161431 | Lxy = 0.00000000 | Lxz = 0.00000000 |
|:-----------------|:-----------------|:-----------------|
| Lyx = 0.00000000 | Lyy = 0.00161431 | Lyz = 0.00000000 |
| Lzx = 0.00000000 | Lzy = 0.00000000 | Lzz = 0.00285377 |

Moments of inertia: ( kilograms x square meters ) Taken at the output coordinate system.
| Ixx = 0.00161571 | Ixy = 0.00000000 | Ixz = 0.00000000 |
|:-----------------|:-----------------|:-----------------|
| Iyx = 0.00000000 | Iyy = 0.00161571 | Iyz = 0.00000000 |
| Izx = 0.00000000 | Izy = 0.00000000 | Izz = 0.00285377 |


---


### Drive Spring ###

![http://img52.imageshack.us/img52/8643/drivespring.png](http://img52.imageshack.us/img52/8643/drivespring.png)

Note: Rotation happens about the Z axis (shown in picture but hard to read)

Mass properties of DriveSpring ( Assembly Configuration - Default )

Mass = 2.2937 kilograms

Center of mass: ( meters )
| X = 0.0608 |
|:-----------|
| Y = 0.0759 |
| Z = 0.0264 |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.0188  | Lxy = 0.0083  | Lxz = -0.0037 |
|:--------------|:--------------|:--------------|
| Lyx = 0.0083	 | Lyy = 0.0340  | Lyz = -0.0033 |
| Lzx = -0.0037 | Lzy = -0.0033 | Lzz = 0.0395  |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.0336	| Ixy = 0.0189	| Ixz = 0.0000 |
|:-------------|:-------------|:-------------|
| Iyx = 0.0189	| Iyy = 0.0441	| Iyz = 0.0013 |
| Izx = 0.0000	| Izy = 0.0013	| Izz = 0.0612 |


---


### Lower Leg ###

![http://img31.imageshack.us/img31/1449/lowerlegforatriaswiki.png](http://img31.imageshack.us/img31/1449/lowerlegforatriaswiki.png)

Note: Rotation happens about the X axis (shown in picture but hard to read)

Mass = 0.23427503 kilograms

Center of mass: ( meters )
| X = 0.00000000 |
|:---------------|
| Y = -0.00855999 |
| Z = 0.23010931  |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.00791576 | Lxy = 0.00000038 | Lxz = -0.00000002 |
|:-----------------|:-----------------|:------------------|
| Lyx = 0.00000038 | Lyy = 0.00791850 | Lyz = 0.00015322  |
| Lzx = -0.00000002 | Lzy = 0.00015322 | Lzz = 0.00009204  |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.02033785 | Ixy = 0.00000038 | Ixz = -0.00000002 |
|:-----------------|:-----------------|:------------------|
| Iyx = 0.00000038 | Iyy = 0.02032343 | Iyz = -0.00030824 |
| Izx = -0.00000002 | Izy = -0.00030824 | Izz = 0.00010921  |


---


### Four-bar Linkage ###

![http://img204.imageshack.us/img204/8484/fourbarlinkageforatrias.png](http://img204.imageshack.us/img204/8484/fourbarlinkageforatrias.png)

Note: Rotation happens about the X axis (shown in picture but hard to read)

Mass = 0.16614713 kilograms

Center of mass: ( meters )
| X = 0.00000000 |
|:---------------|
| Y = 0.00000000 |
| Z = 0.26899140 |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.00634936 | Lxy = 0.00000000 | Lxz = 0.00000000 |
|:-----------------|:-----------------|:-----------------|
| Lyx = 0.00000000 | Lyy = 0.00651790 | Lyz = 0.00000000 |
| Lzx = 0.00000000 | Lzy = 0.00000000 | Lzz = 0.00017670 |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.01837117 | Ixy = 0.00000000 | Ixz = 0.00000000 |
|:-----------------|:-----------------|:-----------------|
| Iyx = 0.00000000 | Iyy = 0.01853970 | Iyz = 0.00000000 |
| Izx = 0.00000000 | Izy = 0.00000000 | Izz = 0.00017670 |


---


### Spring Drive + Shin Bone ###

![http://img694.imageshack.us/img694/2901/driveshinforatriaswiki.png](http://img694.imageshack.us/img694/2901/driveshinforatriaswiki.png)

Note: This is a combination of items detailed above. Rotation happens about the X axis (shown in picture but hard to read)

Mass = 3.12775915 kilograms

Center of mass: ( meters )
| X = -0.02002582 |
|:----------------|
| Y = 0.06351119  |
| Z = 0.07496826  |

Moments of inertia: ( kilograms x square meters ) Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.06363035 | Lxy = 0.00283875 | Lxz = 0.00485482 |
|:-----------------|:-----------------|:-----------------|
| Lyx = 0.00283875 | Lyy = 0.05532782 | Lyz = 0.00921206 |
| Lzx = 0.00485482 | Lzy = 0.00921206 | Lzz = 0.02469387 |

Moments of inertia: ( kilograms x square meters ) Taken at the output coordinate system.
| Ixx = 0.09382546 | Ixy = -0.00113933 | Ixz = 0.00015911 |
|:-----------------|:------------------|:-----------------|
| Iyx = -0.00113933 | Iyy = 0.07416091  | Iyz = 0.02410433 |
| Izx = 0.00015911 | Izy = 0.02410433  | Izz = 0.03856456 |


---


### Spring Drive + Thigh Bone ###

![http://img257.imageshack.us/img257/2658/drivethighforatriaswiki.png](http://img257.imageshack.us/img257/2658/drivethighforatriaswiki.png)

Note: This is a combination of items detailed above. Rotation happens about the X axis (shown in picture but hard to read)

Mass = 3.14602732 kilograms

Center of mass: ( meters )
| X = 0.02065429 |
|:---------------|
| Y = 0.06259142 |
| Z = -0.07850895 |

Moments of inertia: ( kilograms x square meters ) Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.06904086 | Lxy = -0.00294897 | Lxz = 0.00520472 |
|:-----------------|:------------------|:-----------------|
| Lyx = -0.00294897 | Lyy = 0.06053653  | Lyz = -0.00872473 |
| Lzx = 0.00520472 | Lzy = -0.00872473 | Lzz = 0.02506415 |

Moments of inertia: ( kilograms x square meters ) Taken at the output coordinate system.
| Ixx = 0.10075704 | Ixy = 0.00111816 | Ixz = 0.00010329 |
|:-----------------|:-----------------|:-----------------|
| Iyx = 0.00111816 | Iyy = 0.08126965 | Iyz = -0.02418426 |
| Izx = 0.00010329 | Izy = -0.02418426 | Izz = 0.03873139 |


---


### Shin Bone ###

![http://img266.imageshack.us/img266/8914/shinbone.png](http://img266.imageshack.us/img266/8914/shinbone.png)

Note: Rotation happens about the X axis (shown in picture but hard to read)

Mass = 0.7515 kilograms

Center of mass: ( meters )
| X = 0.0080 |
|:-----------|
| Y = 0.0345 |
| Z = 0.1275 |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.0193	 | Lxy = -0.0000 | Lxz = -0.0006 |
|:--------------|:--------------|:--------------|
| Lyx = -0.0000 | Lyy = 0.0171  | Lyz = 0.0019  |
| Lzx = -0.0006 | Lzy = 0.0019  | Lzz = 0.0035  |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.0325	| Ixy = 0.0002	| Ixz = 0.0002 |
|:-------------|:-------------|:-------------|
| Iyx = 0.0002	| Iyy = 0.0294	| Iyz = 0.0052 |
| Izx = 0.0002	| Izy = 0.0052	| Izz = 0.0044 |


---


### Thigh Bone ###

![http://img715.imageshack.us/img715/3476/thighbone.png](http://img715.imageshack.us/img715/3476/thighbone.png)

Note: Rotation happens about the X axis (shown in picture but hard to read)

Mass = 0.7432 kilograms

Center of mass: ( meters )
| X = -0.0057 |
|:------------|
| Y = 0.0314  |
| Z = -0.1439 |

Moments of inertia: ( kilograms x square meters )
Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.0229	 | Lxy = 0.0001  | Lxz = -0.0005 |
|:--------------|:--------------|:--------------|
| Lyx = 0.0001	 | Lyy = 0.0208  | Lyz = -0.0019 |
| Lzx = -0.0005 | Lzy = -0.0019 | Lzz = 0.0033  |

Moments of inertia: ( kilograms x square meters )
Taken at the output coordinate system.
| Ixx = 0.0390	 | Ixy = -0.0000 | Ixz = 0.0002  |
|:--------------|:--------------|:--------------|
| Iyx = -0.0000 | Iyy = 0.0362  | Iyz = -0.0052 |
| Izx = 0.0002	 | Izy = -0.0052 | Izz = 0.0041  |


---


### Torso ###

![http://img651.imageshack.us/img651/1902/torsoforatriaswiki.png](http://img651.imageshack.us/img651/1902/torsoforatriaswiki.png)

Note:
  * All numbers below include the two hip motor rotors present in this assembly.
  * The Torso used in the lab will have components that allow it to be mounted to the Boom as well as components that allow the operator to lift the robot. These are not included in the numbers below.
  * Rotation happens about the Z axis (shown in picture but hard to read)

Mass = 16.67894128 kilograms

Center of mass: ( meters )
| X =  0.00067503 |
|:----------------|
| Y =  0.38585133 |
| Z =  -0.00163941 |

Moments of inertia: ( kilograms x square meters ) Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.25184667 | Lxy = 0.00101024 | Lxz = 0.00047153 |
|:-----------------|:-----------------|:-----------------|
| Lyx = 0.00101024 | Lyy = 0.12518370 | Lyz = -0.00323819 |
| Lzx = 0.00047153 | Lzy = -0.00323819 | Lzz = 0.21974136 |

Moments of inertia: ( kilograms x square meters ) Taken at the output coordinate system.
| Ixx = 2.73507305 | Ixy = 0.00535443 | Ixz = 0.00045308 |
|:-----------------|:-----------------|:-----------------|
| Iyx = 0.00535443 | Iyy = 0.12523613 | Iyz = -0.01378879 |
| Izx = 0.00045308 | Izy = -0.01378879 | Izz = 2.70293051  |


---


### Hip Motor Rotor ###

![http://img856.imageshack.us/img856/7167/hipmotorrotorforatriasw.png](http://img856.imageshack.us/img856/7167/hipmotorrotorforatriasw.png)

On the robot, two of these sub assemblies reside in the hip. One for each hip drive actuator. Rotation happens about the Z axis (shown in picture but hard to read)

Mass = 0.84637415 kilograms

Center of mass: ( meters )
| X = 0.00000000 |
|:---------------|
| Y = 0.00000000 |
| Z = 0.00468580 |

Moments of inertia: ( kilograms x square meters ) Taken at the center of mass and aligned with the output coordinate system.
| Lxx = 0.00070706 | Lxy = -0.00000017 | Lxz = -0.00000005 |
|:-----------------|:------------------|:------------------|
| Lyx = -0.00000017 | Lyy = 0.00070794  | Lyz = -0.00000002 |
| Lzx = -0.00000005 | Lzy = -0.00000002 | Lzz = 0.00101319  |

Moments of inertia: ( kilograms x meters ) Taken at the output coordinate system.
| Ixx = 0.00072565 | Ixy = -0.00000017 | Ixz = -0.00000005 |
|:-----------------|:------------------|:------------------|
| Iyx = -0.00000017 | Iyy = 0.00072653  | Iyz = -0.00000002 |
| Izx = -0.00000005 | Izy = -0.00000002 | Izz = 0.00101319  |


---



---


# Hip Joint Range of Motion #

## Toes Together angle ##

![http://img33.imageshack.us/img33/7550/20111107toestogetherfor.png](http://img33.imageshack.us/img33/7550/20111107toestogetherfor.png)

The angle at which the leg reaches a hard stop.

angle = 9.0 degrees


---


## Toes Spread angle ##

![http://img406.imageshack.us/img406/9306/20111107toesspreadforat.png](http://img406.imageshack.us/img406/9306/20111107toesspreadforat.png)

The angle at which the leg reaches a hard stop.

angle = 12.0 degrees

# Hip Width #

![http://img442.imageshack.us/img442/5369/20111107hipwidthforatri.png](http://img442.imageshack.us/img442/5369/20111107hipwidthforatri.png)

hip width = 6.20906 in = 157.71 mm


---



---


# Transmissions #

## Hip Transmission ##

This section details the transmission of the hip drive. This is a cable drive transmission consisting of two pulleys.
| Pulley | Dia (in) | Dia (m) |
|:-------|:---------|:--------|
| Motor Pulley | 1.25     | 0.03175 |
| Output Pulley | 23.65    | 0.60071 |


---


## Leg Transmission(s) ##

Each motor in the leg has a 50:1 (input:output) Harmonic Drive transmission.


---
