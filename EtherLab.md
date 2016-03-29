# Introduction #

EtherLab is a general control system for robotic systems, based around EtherCAT. Since our only realtime I/O on the master side is EtherCAT, it is a viable alternative to our current ROS+Orocos-based system.

EtherLab contains several components, listed at http://etherlab.org/en/components.php

# Versions #

The latest (as of September 2013) stable version of EtherLab is 1.3-rc3, which does not have PREEMPT\_RT support. Therefore, we are using the current development version of EtherLab. As a result, some of the other components aren't the latest releases off etherlab.org.

The following versions of the components are known to work together:
  * Data Logging Service: Latest Mercurial, patched with fl\_choice\_fix in patches\_etc/ directory
  * EtherCAT Master: 1.5.2 (latest release)
  * EtherLab: Latest Mercurial
  * PDServ: Tag release-1.0.0, in the Mercurial repository

# Data Logging Service #

When restarting a job, it appends to the existing data. This causes multiple logging runs to end up in one log output. There may have been a way to select a particular output when exporting log data, but I don't remember for sure. We may need to make some sort of launcher script to select controllers and clear log data.

Also, exporting to .mat format doesn't work. Instead, you need to do the ASCII data. Unfortunately, this loses the names of the various channels -- we should probably create some sort of script to read in these files and fix the channel names.

# Simulation #

The simulation will be built in to the ATRIAS framework, and will be controlled through the TestManager. There will probably be a setting to switch between EtherCAT and the simulation, although this may be done automatically based on the presence of the EtherCAT bus.

Hopefully, we will be able to run the simulation without starting an EtherCAT Master on a wired interface.