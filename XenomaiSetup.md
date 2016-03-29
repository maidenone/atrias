# Introduction #
This page outlines the necessary procedures to install Xenomai on a fresh installation of Ubuntu. Before you start, you should check out the git repository. Be warned, however, that you should **not** build Orocos (namely rtt and ocl) before completing the steps on this page, so skip that.

Note: If you do accidentally build Orocos, make sure to do a full clean (--pre-clean argument for rosmake) before starting the steps listed here, or else you will encounter major problems.

# Installation Procedures #

## Step One: Install Required Software Packages ##
In order to get everything built and set up we'll need a few utilities. Get them by running:
```
sudo apt-get install libncurses5-dev libxerces-c-dev
```

## Step Two: Download and Extract Files ##
The bulk of the work of getting Xenomai set up is that of building a linux kernel patched with Xenomai. The traditional place for building a kernel is in /usr/src, so we'll elevate to root and download all of our files there:
```
sudo su
cd /usr/src
```
First we'll grab Xenomai. The most recent stable release as of the time of writing is 2.6.2.1.
```
wget http://download.gna.org/xenomai/stable/xenomai-2.6.2.1.tar.bz2
tar xjf xenomai-2.6.2.1.tar.bz2
```
Next we need a compatible linux kernel. The newest version of linux that this version of Xenomai supports is 3.5.7.
```
wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.5.7.tar.bz2
tar xjf linux-3.5.7.tar.bz2
```
Those are all of the files we need for now.

## Step Three: Patch the Kernel for Xenomai ##
Now we need to apply the patch to add Xenomai support to our kernel before we build it. This is easily accomplished with the following command:
```
xenomai-2.6.2.1/scripts/prepare-kernel.sh --arch=x86_64 --linux=linux-3.5.7 --ipipe=xenomai-2.6.2.1/ksrc/arch/x86/patches/ipipe-core-3.5.7-x86-3.patch
```
The kernel is now patched and ready to be configured.

## Step Four: Configuring the Kernel ##
Now that we have a patched kernel, we need to configure it to be nice and lean, and have the right options set to play nice with Xenomai. Xenomai is incompatible with any CPU scaling or frequency scaling options and also hates ACPI power-saving options.

Fortunately, the work of creating a good kernel configuration for Xenomai is already done. All we have to do is copy it into our linux source directory. There are two seperate configs. One is for Zotacs (or anything with an Atom in it) and the other is for any other multi-core Intel processor. If you're using AMD or an older Intel, you'll have to tweak the config a little.

Start by changing directory into linux-3.5.7:
```
cd linux-3.5.7
```

If you're running on a different Intel chip run:
```
cp <PATH_TO_ATRIAS>/kernel_configs/xenomai_3.5.7_intel_generic.config .config
```
Using the structure in the rest of the wiki it would be:
```
cp /home/drl/atrias/kernel_configs/xenomai_3.5.7_intel_generic.config .config
```


<PATH\_TO\_ATRIAS>

 is the path to the Atrias working copy you checked out.

All that remains is to build and install it and install the Xenomai libraries.

## Step Five: Building and Installing the Kernel ##
The second-to-last step is to build the kernel. This is a fairly painless process, consisting of four commands executed in order. The first two commands take a -j argument. If you want the kernel to build as quickly as possible, take the number of physical CPU cores in the computer (not including virtual cores from hyperthreading) and multiply it by 1.5 (rounded down to the nearest whole number). Place that number after the -j for each command. Take care not to run a command with a -j without a number after it, or else it will try to use an infinite number of build threads and freeze the computer.

For a dual-core system (e.g. a Zotac) you would run these commands:
```
make -j3
make modules -j3
make modules_install
make install
```

The 3 in -j3 is what you would replace if you were running a system with something other than 2 cores.

These commands will take a very long time to complete on most computers, so it would be best that you find something else productive to do for an hour and a half or so. If you would like the next command to start automatically when the previous one finishes, you can bunch them into one command like so:
```
make -j3 && make modules -j3 && make modules_install && make install
```
Be warned, however, that you may miss any errors that occur if you use this trick.

## Step Six: Installing the Xenomai Libraries ##
Now we need to install the Xenomai libraries. Simply run these commands from the linux-3.5.7 directory:
```
mkdir xenomai_build
cd xenomai_build
/usr/src/xenomai-2.6.2.1/configure --enable-x86-sep --enable-x86-tsc --enable-smp --enable-dlopen-skins
make && make install
```

## Step Seven: Compiling Orocos to work with Xenomai ##
This is the last step! All that needs to be done here is to set some environment variables then to compile Orocos the normal way.

We'd like the environment variables to stick around, so we'll put them in our .bashrc:
```
echo 'export LD_LIBRARY_FLAGS=$LD_LIBRARY_FLAGS:/usr/xenomai/lib' >> ~/.bashrc
echo "export OROCOS_TARGET=xenomai" >> ~/.bashrc
echo 'export PATH=$PATH:/usr/xenomai/bin/' >> ~/.bashrc
echo "export XENOMAI_ROOT_DIR=/usr/xenomai" >> ~/.bashrc
. ~/.bashrc
```

Before we can compile, there are two Ruby libraries that Orocos depends on that aren't listed in the install guide. Install them now:
```
apt-get install ruby-facets ruby-nokogiri
```

And now to compile Orocos!
```
rosmake orocos_toolchain rtt_ros_integration rtt_ros_comm rtt_common_msgs rtt_geometry
```

And we're done! You should be all set to run stuff in your shiny new Xenomai deployer!

## It's About Time! ##