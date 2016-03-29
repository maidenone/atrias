**_Table of Contents_**





---

# Overview #

The purpose of this page is to teach new users to use and understand this simulation.

Current model:
  * The monopod is modeled (ATRIAS v2.0)
  * The biped is modeled using the v2.0 legs and v2.1 hip.
  * Both of these models will be updated to v2.1 as time allows

Software:
  * [Ubuntu 12.04](http://www.ubuntu.com/) is the operating system
  * [Robot Operating System (ROS)](http://www.ros.org/wiki/) and [OROCOS](http://orocos.org/toolchain) provide the communication framework
    * [Gazebo](http://gazebosim.org/) (included in ROS) wraps the physics and visualization engines (currently ODE and OGRE).



---

# Installing the Software #

Follow the [AtriasSetup](AtriasSetup.md) wiki page.

Make the package
```
rosmake atrias_sim
```


---

# Running the Simulation #

Once all the required software has been installed, test the simulation using the following ROS command in a terminal:

```
roslaunch atrias_sim atrias20_leg.launch
```

This command will open the simulation window.  By default the simulation will be paused; press play in the top left to get things moving.


If your goal was just to run the simulation, you can stop here.  If you want to run the GUI and control system as well, execute the following in two more terminals:

```
roslaunch atrias gui.launch
```

```
roslaunch atrias orocos_sim.launch
```




---

# Code Breakdown #

This section explains what processes are created when the above launch file is called.
Sidenote: Each of the ROS nodes can also be launched separately with rosrun.

- roscore: ROS always creates a roscore to handle ROS communications when roslaunch is run.  This is implicit in the launch file and not directly defined.

- simulation\_server ROS node: This calls gazebo to run its physics engine and load the .world file.  This world file contains all of the simulation parameters and links to plugins.  These plugins can control any simulation/robot property, and also communicate with outside programs (in this case the controller node).
```
<node name="simulation_server" pkg="gazebo" type="gazebo" args="$(find atrias_sim)/worlds/atrias20_leg.world" respawn="false" output="screen" />
```

- simulation\_gui ROS node: This is the GUI frontend of Gazebo that runs OGRE for rendering.
```
<node name="simulation_gui" pkg="gazebo" type="gui" respawn="false" output="screen" />
```

- controller ROS node: This runs an OROCOS script that runs the communications manager in the atrias\_rt\_ops package.
```
<node name="rt_ops" pkg="ocl" type="deployer-gnulinux" args="-s $(find atrias_rt_ops)/sim_test.ops -l info --" respawn="false" output="screen" />
```


### Important Notes for Modeling ###

**Units**
  * Any arbitrary units can be used so long as they are consistent.  This code uses kilograms, meters, and seconds.

**Links**
  * Link origins are defined with respect to the model origin.
  * The visual and collision geometry always spawn along the z-axis of the link until rotated.

**Joints**
  * Joint origins are defined with respect to the child link origin.