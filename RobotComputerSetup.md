# Introduction #

This page documents things that must be done to set up a robot control computer. It is also required to complete the steps on AtriasSetup and XenomaiSetup pages; this page only covers installation steps specific to the robot computer.

# Network Configuration #
## Host file ##
GUI computer IP
## Hostname ##
i1000a-#
## Static IP ##

# ROS\_MASTER\_URI #
Since the ROS master runs on the GUI laptop, we must ensure that the ROS\_MASTER\_URI environment variable points to the laptop. To set this permanently, run this command as the drl user:
```
echo 'export ROS_MASTER_URI="http://drl-guilaptop:11311"' >> ~/.bashrc
```

# Apply Settings #
To apply all of the changes made, run this command to execute your .bashrc script:
```
. ~/.bashrc
```

And you're done!