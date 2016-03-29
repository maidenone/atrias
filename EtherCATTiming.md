Here's the desired timing for one full cycle:
  1. DC interrupt fires
  1. Medulla reads the sensors and timestamps those that need timestamps via the µcontroller's internal timer.
  1. Medulla updates the data on the ESC and reads new motor torque commands from ESC
  1. The EtherCAT Master sends out an ECat frame to retrieve the new sensor data while (or after) the Medulla updates the motor outputs.
  1. The EtherCAT Master reads out the data from the returned frame and sends it on to the controllers.
  1. The EtherCAT Master receives new torque commands from the controllers and sends out a new frame with the new commands. Then the EtherCAT Master goes back to sleep.

# SOEM #
For SOEM, DC configuration is one-time and does not require calling any functions periodically. However, while SOEM automatically syncs the slaves to the "reference clock" (the first slave w/ DC clock support), it does not automatically sync the slaves with the master. However, it is not difficult to use SOEM's API to sync it ourselves, as described at http://lists.berlios.de/pipermail/soem-user/2012-July/000129.html

SOEM has satisfactory realtime performance.

# EtherLabs #
EtherLabs requires that your periodically call functions to keep the DCs synchronized, but it is capable of syncing the DC with the master's clock.

However, EtherLabs has no ability to wait for an EtherCAT packet to return. Instead, we must simply wait an arbitrary amount of time (if we had the exact packet size, we could calculate it... but we don't, so we can only estimate it).