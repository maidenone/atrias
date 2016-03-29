<a href='Hidden comment: 
vim: syntax=off
'></a>

# Introduction #

This page describes all the changes needed to customize a kernel config for a given machine as well as the reasons for our choices in various config settings.

It also contains a few other notes for configuring a realtime system.

# Debian RT Kernel #

The standard Debian repositories contain a PREEMPT\_RT kernel. While this kernel will not offer the best realtime performance possible on a given machine, it should offer performance sufficient for our purposes. This kernel may be installed on an Ubuntu machine.

The name of the package for the amd64 architecture is linux-image-rt-amd64. This is a metapackage that depends on the current RT kernel version. It has some dependencies that are not met by standard Ubuntu components, but all dependencies may be downloaded off Debian's website (should only be 1 or 2 extra packages in total).

Since the kernel comes fully-featured, we will need to disable CPU frequency scaling for realtime operation. The following line, placed into /etc/rc.local, will do so:
```
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

# Priority Setup #

To do EtherCAT in realtime, the networking driver's IRQ needs to have a realtime priority. The following line, placed in /etc/rc.local, will set the prority to 97 automatically (replace eth0 with the adapter's name):
```
sudo chrt -p 97 $(ps -o pid,cmd ax | grep eth0 | grep irq | awk '{ print $1 }')
```

This could probably be done by the EtherCAT connector at load time.

# Testing #

Based on our loop timings, we would like the worst-case latency to be under 200 microseconds; PREEMPT\_RT should be able to achieve a maximum latency of under 100 microseconds.

The cyclictest program may be used to test the maximum latency of a system. It is available in the rt-tests package is the standard Ubuntu repositories.

For realtime operation, cyclictest needs at least 3 parameters:
  * -p98 (To set the priority above the priority of most of the kernel itself)
  * -m (Locks memory to prevent page faults)
  * -n (Tells it to use nanosleep(); the default choice isn't realtime-safe)

Alternatively, the -S flags sets up some "standard SMP test" flags for you. I recommend the following command line for a thorough test:
```
sudo cyclictest -i100 -p98 -S -d0 -m
```
This runs cyclictest at 10kHz on all cores, and should identify any latency that occurs.

Additionally, some sort of system load should be used during the test. A parallel kernel compilation (enclosed in a while [true ](.md) loop) generates realistic load. Additionally, you may use the "stress" program to easily generate io, disk, cpu, and memory allocation load.

# Things Needing Customization #

Here is a list of things that need to be customized per-computer in the config files:
  * Processor type and features -> Processor Family
> > This should be set based upon the processor in a given computer (it affects optimization and compilation settings).

# Reasoning for Choices #

This section explains the reasoning behind choices made in the kernel config.
Config options are presented in the hierarchy visible via 'make menuconfig' (or by the setting name if the hierarchy was not available at the moment).

```
General setup --->
	[*] Support for paging of anonymous memory (swap)
```
This is needed in order to enable swap partitions. Since we lock our memory, this has no impact on realtime, but it prevents the
out of memory killer from activating during compilations.

```
General setup --->
	[*] System V IPC
```
The chromium web browser, possibly along with other applications, needs this. Since this does no harm, we enable it.

```
General setup --->
	[*] POSIX Message Queues
```
These are utilized by Orocos, and it may not be the only software needing these. These do no harm to realtime, so they're enabled.

```
General setup --->
	[*] open by fhandle syscalls
```
These sound cool. I don't know what apps need them yet, but we'll enable them just in case.

```
General setup --->
	[*] Auditing support
```
See "Enable system-call auditing support" below.

```
General setup --->
	[*]   Enable system-call auditing support
```
This is required for some applications, particularly those needing to see what files are being accessed at a given time.

```
General setup --->
	[*]   Make audit loginuid immutable
```
Sounds like a good idea, shouldn't affect realtime.

```
General setup --->
	IRQ subsystem  --->
		[ ] Expose hardware/virtual IRQ mapping via debugfs
```
This is unnecessary -- we wouldn't know what to do with this if it was enabled.

```
General setup --->
	Timers subsystem  --->
		[*] Tickless System (Dynamic Ticks)
```
This will save some power and possibly reduce the number of interrupts bothering our code.

```
General setup --->
	Timers subsystem --->
		[*] High Resolution Timer Support
```
We need high resolution timer support -- otherwise, we could only sleep for multiples of 1ms!

```
General setup --->
	CPU/Task time and stats accounting  --->
		Cputime accounting (Simple tick based cputime accounting)  --->
```
We don't need super-perfect cputime accounting, and this choice should perform better.

```
General setup --->
	CPU/Task time and stats accounting  --->
		[*] BSD Process Accounting
```
This is a useful feature for some programs.

```
General setup --->
	CPU/Task time and stats accounting  --->
		[*]   BSD Process Accounting version 3 file format
```
All the tools I've seen that utilize BSD Process Accounting parse this version.

```
General setup --->
	CPU/Task time and stats accounting  --->
		[ ] Export task/process statistics through netlink (EXPERIMENTAL)
```
Unlike the BSD Process Accounting options, this seems useless, and is marked experimental.

```
General Setup --->
	RCU Subsystem  --->
		RCU Implementation (Preemptible tree-based hierarchical RCU)  --->
```
This was the only option available.

```
General Setup --->
	RCU Subsystem  --->
		[ ] Consider userspace as in RCU extended quiescent state
```
This is only for kernel hacking -- it sounds like at this point, it will break the kernel if enabled.

```
General Setup --->
	RCU Subsystem  --->
		(32) Tree-based hierarchical RCU fanout value
```
We have no need to change this, and the help says to just take the default.

```
General Setup --->
	RCU Subsystem  --->
		(16) Tree-based hierarchical RCU leaf-level fanout value
```
Again, we have no need to change this, so taking the default.

```
General Setup --->
	RCU Subsystem  --->
		[ ] Disable tree-based hierarchical RCU auto-balancing
```
This is only useful for testing the kernel's RCU system. Enabling this will probably hurt performance.

```
General Setup --->
	RCU Subsystem  --->
		[ ] Enable RCU priority boosting
```
At first, the help seems to indicate that this is good. However, some other research I've done indicates that this is only useful if the
realtime process is CPU-bound, which ours isn't. Therefore, this needs to remain disabled (it could potentially lead to preemption of our
processes, although that's unlikely since it waits dozens to hundreds of milliseconds to take effect).

```
General Setup --->
	RCU Subsystem  --->
		[ ] Offload RCU callback processing from boot-selected CPUs
```
This only applies to selected CPUs, and you cannot select every CPU, so it's not useful to us (we don't want to utilize
hacks such as affinity tuning).

```
General Setup -->
	Choose SLAB allocator (SLUB (Unqueued Allocator)) (CONFIG_SLUB)
```
I've looked around, and SLUB performs better on RT kernels, so I'll select it.

```
General Setup -->
	[ ] Memory placement aware NUMA scheduler
```
None of our systems have a Non-Uniform Memory Architecture, so we'll deselect this.

```
[*] Enable loadable module support --->
	[ ] Module signature verification
```
We don't use this, and this can leads to problems. Disable.

```
Processor type and features --->
	[ ] Enable to assign a node which has only movable memory
```
We don't care about memory or CPU hotplug, so we'll deselect this.

```
Processor type and features --->
	[ ] Allow for balloon memory compaction/migration (BALLOON_COMPACTION)
```
We don't need memory ballooning (which may be used by guests in virtual machines), so we'll deselect this.

```
Processor type and features --->
	  [ ] Set default setting of cpu0_hotpluggable (BOOTPARAM_HOTPLUG_CPU0)
```
We don't use CPU hotplugging -- deselect.

```
Processor type and features --->
	  [ ] Debug CPU0 hotplug (DEBUG_HOTPLUG_CPU0)
```
Same as for the previous option -- disable.

```
Power management and ACPI options --->
	[*] ACPI (Advanced Configuration and Power Interface) Support
		[*] ACPI tables override via initrd (ACPI_INITRD_TABLE_OVERRIDE)
```
This has no disadvantages, and may allow the distribution's initial ramdisk to work around firmware issues, so I enabled it.

```
-*- Networking support --->
	Networking options --->
		<M>   Packet: sockets monitoring interface (PACKET_DIAG)
```
This is used by some networking tools (possibly the EtherCAT master as well?) for raw access. We'll compile it as a module, so it'll be loaded if necessary.

```
-*- Networking support --->
	Networking options --->
		<*> The IPv6 protocol --->
			<M> IPv6: GRE tunnel (IPV6_GRE)
```
This may turn out to be useful, but is only loaded if needed -- I made this a module.

```
-*- Networking support --->
	Networking options --->
		[*] Network packet filtering framework (Netfilter) --->
			IP: Netfilter Configuration --->
				<M>   IPv4 NAT (NF_NAT_IPV4)
```
Like other module-capable options, we might as well compile this as a module.

```
-*- Networking support --->
	Networking options --->
		[*] Network packet filtering framework (Netfilter) --->
			IPv6: Netfilter Configuration --->
				<M>   IPv6 NAT (NF_NAT_IPV6)
```
This option is similar to NF\_NAT\_IPV4 above -- module.

```
-*- Networking support --->
	Networking options --->
		[*] Network packet filtering framework (Netfilter) --->
			IPv6: Netfilter Configuration --->
				<M>     MASQUERADE target support (IP6_NF_TARGET_MASQUERADE)
```
This one is also a module, and is only loaded if necessary. Harmless, so we'll make it a module.

```
-*- Networking support --->
	Networking options --->
		[*] Network packet filtering framework (Netfilter) --->
			IPv6: Netfilter Configuration --->
				<M>     NPT (Network Prefix translation) target support (IP6_NF_TARGET_NPT)
```
This is also harmless, so we'll make it a module in case we ever want it.

```
-*- Networking support --->
	Networking options --->
		{M} The SCTP Protocol --->
			Default SCTP cookie HMAC encoding (MD5) (SCTP_DEFAULT_COOKIE_HMAC_MD5)
```
The help tells us to default to MD5, so we'll do so.

```
-*- Networking support --->
	Networking options --->
		{M} The SCTP Protocol --->
			[ ] Enable optional SHA1 hmac cookie generation (SCTP_COOKIE_HMAC_SHA1)
```
SCTP is not really designed for security -- this isn't necessary, and since it can't be made a module, we'll compile it out.

```
-*- Networking support --->
	Networking options --->
		<M> The TIPC Protocol (EXPERIMENTAL) --->
			Maximum number of ports in a node (TIPC_PORTS) (8191)
```
We'll just take the default, 8191, on this.

```
-*- Networking support --->
	Networking options --->
		[ ]   Distributed ARP Table (BATMAN_ADV_DAT)
```
We don't do mesh networking, so we'll disable this.

```
Device Drivers --->
	<M> Memory Technology Device (MTD) support --->
		<M> Enable UBI - Unsorted block images --->
			Maximum expected bad eraseblock count per 1024 eraseblocks (MTD_UBI_BEB_LIMIT) (20)
```
Let's leave this at the default, 20.

```
Device Drivers --->
	<M> Memory Technology Device (MTD) support --->
		<M> Enable UBI - Unsorted block images --->
			[ ] UBI Fastmap (Experimental Feature) (MTD_UBI_FASTMAP)
```
We don't use this system -- disable.

```
Device Drivers --->
	SCSI device support --->
		[*] SCSI low-level drivers --->
			(128)   LSI MPT Fusion Max number of SG Entries (16 - 256) (SCSI_MPT3SAS_MAX_SGE)
```
We'll just take the default for this (we have no reason to change it).

```
Device Drivers --->
	SCSI device support --->
		[*] SCSI low-level drivers --->
			[ ]   LSI MPT Fusion logging facility (SCSI_MPT3SAS_LOGGING)
```
We don't need logging in some random driver. Deselect.

```
Device Drivers --->
	-*- Network device support --->
		[*] Wireless LAN --->
			<M> Atheros Wireless Cards --->
				[*]   Use Clear-On-Read mode for ISR registers for wil6210 (WIL6210_ISR_COR)
```
As indicated by the help, this should only be deselected if we want to debug this specific driver. Enable.

```
Device Drivers --->
	-*- Network device support --->
		[*] Wireless LAN --->
			[ ] Broadcom device tracing (BRCM_TRACING)
```
According to the help, this is for debugging and can (slightly) hinder performance. Deselect.

```
Device Drivers --->
	Character devices --->
		Serial drivers --->
			[ ] MAX310X support (SERIAL_MAX310X)
```
This doesn't seem to be necessary for any of our hardware. Since it can't be built as a module, we'll deselect it.

```
Device Drivers --->
	Character devices --->
		Serial drivers --->
			(1)   Number of ARC UART ports (SERIAL_ARC_NR_PORTS)
```
We'll leave this at the default, one, since I'm not aware that this UART is in any of our hardware at all.

```
Device Drivers --->
	-*- Power supply class support --->
		[ ] Board level reset or power off ---> (POWER_RESET)
```
On PCs and newer UEFI-based systems, this is done through ACPI, so we don't need this. Deselect.

```
Device Drivers --->
	{*} Generic Thermal sysfs driver --->
		Default Thermal governor (step_wise) (THERMAL_DEFAULT_GOV_STEP_WISE)
```
I'm not 100% sure what this is, but we'll leave it at the default.

```
Device Drivers --->
	{*} Generic Thermal sysfs driver --->
		[ ] Fair-share thermal governor (FAIR_SHARE)
```
We don't care about thermal governing, so disable this.

```
Device Drivers --->
	{*} Generic Thermal sysfs driver --->
		[ ] User_space thermal governor (USER_SPACE)
```
I don't think we need this, so I'm disabling it.

```
Device Drivers --->
	Sonics Silicon Backplane -->
		[ ] SSB GPIO driver (SSB_DRIVER_GPIO)
```
I don't think we need this, so I'm disabling it.

```
Device Drivers --->
	Broadcom specific AMBA --->
		[ ] BCMA GPIO driver (BCMA_DRIVER_GPIO)
```
This also seems unnecessary, so I'm disabling it.

```
Device Drivers --->
	Multifunction device drivers --->
		[ ] TI TPS80031/TPS80032 Power Management chips (MFD_TPS80031)
```
Since we don't have any single-board computers, we probably don't need this.

```
Device Drivers --->
	Multifunction device drivers --->
		[ ] Support for the SMSC ECE1099 series chips (MFD_SMSC)
```
This doesn't seem necessary, and since it can't be compiled as a module, I'll go ahead and disable it.

```
Device Drivers --->
	Multifunction device drivers --->
		[ ] Dialog Semiconductor DA9055 PMIC Support (MFD_DA9055)
```
Disabled with same reasoning as for the TI TPS80031 driver (MFD\_TPS80031)

```
Device Drivers --->
	Multifunction device drivers --->
		[*] Texas Instruments LP8788 Power Management Unit Driver (MPD_LP8788)
```
This seems like it could be in a laptop, so I'll enable it.

```
Device Drivers --->
	Multifunction device drivers --->
		[ ] Support for AS3711 (MFD_AS3711)
```
This seems to be some sort of IC, so I'll assume that if it's needed, another driver will select it. Deselect.

```
Device Drivers --->
	-*-- Voltage and Current Regulator Support --->
		[ ] TI LP8788 Power Regulators (REGULATOR_LP8788)
```
Deselecting, since we don't need to control voltages (even if we have this chip).

```
Device Drivers --->
	<M> Multimedia support --->
		[ ] Enable advanced debug functionality on V4L2 drivers (VIDEO_ADV_DEBUG)
```
We're not debugging webcam drivers, so we don't need this -- deselect.

```
Device Drivers --->
	<M> Multimedia support --->
		[ ] Enable old-style fixed minor ranges on drivers/video devices (VIDEO_FIXED_MINOR_RANGES)
```
We don't need this -- Ubuntu is udev-based (besides, we don't need webcams on the robot, at least not yet).

```
Device Drivers --->
	<M> Multimedia support --->
		[*] Media USB Adapters (MEDIA_USB_SUPPORT)
```
This seems like it might be important -- selecting.

```
Device Drivers --->
	<M> Multimedia support --->
		[*] Media PCI Adapters (MEDIA_PCI_SUPPORT)
```
This also seems like it might be important -- selecting.

```
Device Drivers --->
	<M> Multimedia support --->
		Customise DVB Frontends --->
			< > Dummy frontend driver (DVB_DUMMY_FE)
```
We don't need to develop video drivers, so we'll deselect this.

```
Device Drivers --->
	Graphics support --->
		(5)   Maximum debug level (NOUVEAU_DEBUG)
```
We'll leave this at default, since it's reasonable.

```
Device Drivers --->
	Graphics support --->
		(3)   Default debug level (NOUVEAU_DEBUG_DEFAULT)
```
We'll also leave this at its (reasonable) default value.

```
Device Drivers --->
	-*- LED Support --->
		[ ] LED CPU Trigger (LEDS_TRIGGER_CPU)
```
We don't have any large machines (where this might be useful), so we'll disable it.

```
Device Drivers --->
	[*] Staging drivers --->
		[ ] Silicom devices
```
We don't have any Silicom adapters, so we'll disable it.

```
Device Drivers --->
	<M> Industrial I/O support --->
		[ ]   IIO callback buffer used for push in-kernel interfaces (IIO_BUFFER_CB)
```
This doesn't have any functionality on its own; it'll be selected if it's necessary. Since it doesn't seem to be selected by anything else, we'll deselect it.

```
Device Drivers --->
	<M> Industrial I/O support --->
		Analog to digital converters --->
			[ ] LP8788 ADC driver (LP8788_ADC)
```
We don't need to read on-motherboard voltages, even if we had this device. Disabled.

```
Device Drivers --->
	<M> Industrial I/O support --->
		Hid Sensor IIO Common --->
			[ ]   ENUM base quirks for HID Sensor IIO drivers (HID_SENSOR_ENUM_BASE_QUIRKS)
```
I'm pretty sure we don't need this -- disabled.

```
File systems --->
	[ ]   Ext4 POSIX Access Control Lists (EXT4_FS_POSIX_ACL)
```
We don't need ACLs, so we'll disable them.

```
File systems --->
	  [ ] Ext4 Security Labels (EXT4_FS_SECURITY)
```
Like ACLs, we don't need security labels. Disable.

```
File systems --->
	[*] Miscellaneous filesystems --->
i		[ ]   F2FS Status Information (F2FS_STAT_FS)
```
We don't need additional status info for this (relatively rare) filesystem. Disable.

```
File systems --->
	[*] Miscellaneous filesystems --->
		[ ]   F2FS extended attributes (F2FS_FS_XATTR)
```
We also don't need extended attributes, ACLs, or security labels... disable.

```
File systems --->
	[*] Network File Systems --->
		[ ]   Enable CIFS debugging routines (CIFS_DEBUG)
```
We don't need to debug random network filesystems. Disable.

```
File systems --->
	[*] Network File Systems --->
		[ ]   SMB2 network file system support (EXPERIMENTAL) (CIFS_SMB2)
```
This is highly experimental as of kernel 3.8.11 -- disable.

```
Security options --->
	[ ]   Yama stacked with other LSMs (SECURITY_YAMA_STACKED)
```
We don't need additional Linux security systems. Disable.