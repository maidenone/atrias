# Desired features for the ATRIAS software stack #

  * Easy [installation](SoftwareInstall.md).
  * [Modularity](ROS.md) in [code structure](CodeStructure.md) and system [operation](Operation.md).
  * Minimal custom code (i.e., low maintainence).
  * Hard [real-time](RealTime.md) performance in [user space](Orocos.md).

(The links point to wiki pages that explain how we are trying to accomplish these goals.)


# TODO #
  * Does user space EtherCAT lag more than its kernel space counterpart?
  * Document how to set up Orocos-ROS services integration.
  * Reorganize software stack so our main ROS stack is named "atrias" and dump all old test code.

## After code reorganization ##
  * Get a ROS wiki.
  * Set up system to easily convert controllers written in MATLAB to C.
  * Look into Orocos iTaSC, which might be able to replace our controller wrapper (plus more features).
  * ~~Look into [lqt](https://github.com/mkottman/lqt) for Lua-Qt integration to launch components with a GUI.~~ The current scheme of the GUI sending controller requests works just fine.

# Getting Started #

~~We use git as our version control system. [Pro Git](http://progit.org/book/) is a great book for learning to use git.~~