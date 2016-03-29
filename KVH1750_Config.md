

# KVH 1750 IMU Configuration #

Use `atrias/software/atrias/scripts/kvh_comm.py` to configure and debug the IMU. The script is configured for 921600 baud operation. You can change this setting on line 8 of the script.

The script assumes the IMU is out of config mode on startup, thus will print a hexdump of everything it sees on the specified serial device. Once you enter config mode with `=config,1`, it will print everything as-is until you exit config with `=config,0`.

The IMU is configured for 1 kHz internal MSync by default. We should change this:

```
yoos@hephaestus:~/devel/atrias/software/atrias/scripts > ./kvh_comm.py /dev/ttyACM0
KVH 1750 >
<long string of binary gibberish removed>
KVH 1750 > =config,1
CONFIG,1

KVH 1750 > ?help
Following commands are available:
AXES: Get/set axes of orientation
BAUD: Get/set baud rate
CONFIG: Enter/exit user configuration mode
DR: Get/set data rate in normal mode
ECHO: Communications testing
FC: Get/set filter coefficients
FILTEN: Gets/sets if the filter is enabled
FILTTYPE: Selects between Chebychev (default) or Butterworth
HELP: List the available commands
IS: Gets the systems serial number
LINFMT: Set linear output format in normal mode
LINUNITS: Set linear output units in normal mode
MSYNC: Gets/sets the clock source to either internal (IMU) or external (EXT)
RESTART: Restarts the bootloader
ROTFMT: Set rotational output format in normal mode
ROTUNITS: Set rotational output units in normal mode
RSTCFG: Resets the configuration to factory defaults
SELFTEST: Performs an extended BIT while in configuration mode
TEMP: Gets the current temperature
TEMPUNITS: Set temperature output units in normal mode
TESTFILT: Tests the impulse responses of the current filter coefficients
TTG: Tells the unit to enter pass-through mode.  All commands go to the GCB
UPGRADE: Enter upgrade mode
USECRC: Upgrade using a CRC or the intel Hex checksum
VOLT: Gets the voltages on the board
WS: Report the software versions

KVH 1750 > ?msync
MSYNC,IMU

KVH 1750 > =msync,ext
MSYNC,EXT

KVH 1750 > =config,0
KVH 1750 >
fe81ff553c147f01baf511123b07a9a13d0673ad3b95292d3f8c5462000c00272af6d299
KVH 1750 > q
yoos@hephaestus:~/devel/atrias/software/atrias/scripts >
```

You may also want to set `ROTUNITS` to radians instead of degrees, if it isn't already.

Refer to the manual for details.
