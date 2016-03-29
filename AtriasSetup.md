# Xubuntu Installation (gui and robot) #

Open a new terminal and navigate to the folder you want to download the image to.
```
cd ~/Downloads
```

Download Xubuntu 12.04.1 desktop amd64 from http://old-releases.ubuntu.com/releases/xubuntu/releases/12.04/release/.
```
wget http://old-releases.ubuntu.com/releases/xubuntu/releases/12.04/release/xubuntu-12.04.1-desktop-amd64.iso
```

Insert a USB drive and determine which drive letter it is.
```
sudo fdisk -l
```

Unmount the USB device. (In this case, fdisk showed the USB device was sdc. Most of the time its sdb or sdc, but it is almost never sda! Also, specify as a device, sdc, and not a partition, sdc1 or sdc2!)
```
umount /dev/sdc
```

Clone the .iso image over to the USB device.
```
sudo dd if=~/Downloads/xubuntu-12.04.1-desktop-amd64.iso of=/dev/sdc
```

Alternatively, you can use unetbootin or startup creator http://www.ubuntu.com/download/desktop/create-a-usb-stick-on-ubuntu to create the live cd in either windows or linux. There are plenty of guides available by searching Google.

You should then boot and install the OS as normal.
Username = drl
Password = robot
Hostname = i1000a-#


# ATRIAS Git Repository (gui and robot) #

Verify that you have git installed.
```
sudo apt-get install -y git
```

Navigate to your home directory and clone the repository.
```
cd ~
git clone https://code.google.com/p/atrias/
```

To stay authenticated, follow the instructions on the source tab. https://code.google.com/p/atrias/source/checkout


# Xenomai (robot only) #

You do not need a real-time system for most testing, but real-time is needed to operate an actual robot. We currently (as of October 3, 2012) use Xenomai for real-time. Instructions for installing Xenomai are available on the XenomaiSetup page.

Note: Xenomai, should be installed before Orocos or SOEM!


# ROS (gui and robot) #

Install Desktop-Full Fuerte per the instructions on [this ROS wiki page](http://www.ros.org/wiki/fuerte/Installation/Ubuntu).

For both the normal user and root, make sure these lines are somewhere in ~/.bashrc:
```
# ROS
source /opt/ros/fuerte/setup.bash
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/home/drl/rosstacks/:/home/drl/atrias/:/home/drl/atrias/software/atrias_controllers/
```

# Orocos (gui and robot) #

Install Orocos ROS stack per the instructions on [this Orocos wiki page](http://www.ros.org/wiki/orocos_toolchain_ros) under the heading **Manual Installation**.

For both the normal user and root, make sure these lines are somewhere in ~/.bashrc:
```
# Orocos
source `rosstack find orocos_toolchain`/env.sh
```


# RTNet (robot only) #

Under Xenomai, RTNet is required in order to do real-time EtherCAT.

Download and unpack RTNet.
```
cd ~/linux # (or /usr/src, if that's where you build your kernels).
wget http://www.rtnet.org/download/rtnet-0.9.13.tar.bz2
tar xjf rtnet-0.9.13.tar.bz2
cd rtnet-0.9.13
```

Copy over our config file, and configure RTNet. Note: You will need to select the correct driver for your ethernet card (and disable the e1000e driver) if a different card will be used for EtherCAT.
```
cp ~/atrias/kernel_configs/rtnet_config_e1000e .rtnet_config
make menuconfig
```

Build RTNet.
```
make
sudo make install
```

Then put the following into /etc/rc.local (before the "exit 0" line) to configure RTNet at startup (you will need to change things if you're not using an e1000e card).
```
modprobe -r e1000e
insmod /usr/local/rtnet/modules/rtnet.ko
insmod /usr/local/rtnet/modules/rtpacket.ko
insmod /usr/local/rtnet/modules/rt_e1000e.ko
/usr/local/rtnet/sbin/rtifconfig rteth0 up
```

Reboot to finish RTNet configuration.


# EtherCAT #

You only need to install an EtherCAT master if you intend on executing our EtherCAT code (available in the atrias\_ecat\_conn package). We use SOEM as our EtherCAT master, so if you need EtherCAT to work, then you should probably install SOEM.

We use EtherLabs's master to flash the EtherCAT chips. Additionally, it may be useful for its diagnostic capabilities and as a backup EtherCAT master. Therefore, instructions are provided for installing EtherLabs's master. You don't need EtherLabs just to run the robot or communicate with Medullas.


## SOEM (gui and robot) ##

Download the soem library somewhere ROS can find it.
```
cd ~/rosstacks
git clone http://git.mech.kuleuven.be/robotics/soem.git
roscd soem_core
```

At this point, we need to apply some patches, which make SOEM realtime-safe under Xenomai and fix the slaveinfo build.
```
git apply ~/atrias/patches_etc/soem.patch
cp ~/atrias/patches_etc/rt_fix.patch .
```

Someone accidentally committed a change that disables the RTNet build. Open up the Makefile in soem\_core and remove the following line:
```
EXTRA_CMAKE_FLAGS=-DENABLE_RTNET=OFF
```


## EtherLabs ##

Install Mercurial.
```
sudo apt-get install mercurial
```

Check out EtherLab's EtherCAT Master v1.5 to /usr/src.
```
cd /usr/src
sudo hg clone http://etherlabmaster.hg.sourceforge.net:8000/hgroot/etherlabmaster/etherlabmaster etherlabmaster
cd etherlabmaster
sudo hg update stable-1.5
```

Compile (note: the configure should be done while running the same kernel as you will be using when you need EtherLab).
```
sudo ./bootstrap
sudo ./configure --disable-8139too --enable-generic
sudo make all modules
sudo make modules_install install
```

With automake v1.14, I had to add `AUTOMAKE_OPTIONS = subdir-objects` at the top of tools/Makefile.am for bootstrap to work.

Create the startup scripts and update the modules list.
```
sudo cp ./script/init.d/ethercat /etc/init.d/ && sudo chmod 755 /etc/init.d/ethercat
sudo mkdir /etc/sysconfig && sudo cp ./script/sysconfig/ethercat /etc/sysconfig/
sudo depmod
```

Edit /etc/sysconfig/ethercat so the master can attach to the ethernet hardware. Find variables MASTER0\_DEVICE and DEVICE\_MODULES in the script and edit them to look like.
```
MASTER0_DEVICE="ff:ff:ff:ff:ff:ff"

DEVICE_MODULES="generic"
```

Add the scripts to the startup.
```
sudo update-rc.d ethercat defaults
```

Open up /etc/environment and add /opt/etherlab/bin to the PATH variable so it looks something like this.
```
PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/opt/etherlab/bin"
```


# Other Things #

## Vim ##

We use Vim a lot (although it's not required). Since we have a mix of tab-based-indentation files and space-based-indentation files, we have modelines at the end of many files that set vim to follow those styles.

Here is the line to place into /etc/vim/vimrc.local (or any other vimrc) to enable modelines.
```
set modeline
```

## GUI ##

If you are planning to run the robot GUI on your machine, you need to install libgtkmm as well. This can be accomplished with the following command.
```
sudo apt-get install libgtkmm-2.4-dev
```

## Roslaunch via Sudo ##

For security reasons, sudo clears the environment before running commands. This interferes with roslaunch. The following commands install a file that configures sudo to use an environment suitable for running our system through roslaunch.
```
roscd atrias
sudo cp ../../patches_etc/sudo_ros /etc/sudoers.d
sudo chmod 440 /etc/sudoers.d/sudo_ros
echo alias sudo=\'sudo LD_LIBRARY_PATH=$LD_LIBRARY_PATH\' >> ~/.bashrc
```


# Configure and Compile #

The motor and leg encoder calibration values differ from robot to robot. Depending on which biped you have, you will need to navigate to robot\_definitions and create a symlink similar to the following.
```
ln -s biped2_variant_defs.h robot_variant_defs.h
```

Then, compile all software with.
```
rosmake atrias
roscd atrias_controllers
rosmake *
```