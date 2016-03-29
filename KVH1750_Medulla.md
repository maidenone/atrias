

# KVH 1750 IMU Medulla #

When configured for the IMU, the Medulla uses the following pins:

  * F2, F3 (USARTF0) for IMU TX and RX, respectively
  * F1 for IMU MSync
  * B4 for IMU TOV\_Out.

The IMU communicates with the Medulla over RS422 at 921600 baud. F2 and F3 are
routed to a SN65LVDS049 (on the Menial), a dual LVDS transceiver PHY. The MSync
pin is also routed to the LVDS PHY, and the IMU cable is assembled so the IMU
plugs into the positive output pin on the LVDS PHY.

Pin B4 is currently left floating on the Medulla. This should probably be pulled low.

## External crystal oscillator ##
The Medulla (v1.5) does not employ an external crystal oscillator for the
onboard ATXmega, which results in packet corruption between the IMU and the
Medulla. The problem is detailed [here](KVH1750_Medulla_UART_Error.md).

Adding a 16 MHz crystal oscillator (Digi-Key XC1664CT-ND) with 18 pF load
capacitors (Digi-Key 311-1415-1-ND) appears to fix this issue.

We are interested in pins PR0 and PR1 (91 and 92, or XTAL2 and XTAL1, respectively):

<img src='http://wiki.atrias.googlecode.com/git/kvh1750_medulla_xtal_pins.jpg' width='600' />

The crystal and load capacitors:

<img src='http://wiki.atrias.googlecode.com/git/kvh1750_crystal_osc_ready.jpg' width='200' />

Installed on Xmega with hot glue:

<img src='http://wiki.atrias.googlecode.com/git/kvh1750_crystal_osc_installed.jpg' width='600' />

Check solder joints:

<img src='http://wiki.atrias.googlecode.com/git/kvh1750_crystal_osc_sideview.jpg' width='600' />

Tie to nearest easily-accessible ground:

<img src='http://wiki.atrias.googlecode.com/git/kvh1750_crystal_osc_final.jpg' width='600' />

### Double check! ###
Once the clock is initialized, there should be a 650 and 450 mVpp sine wave on
XTAL1 and XTAL2, respectively.

This particular Medulla suffered a greater than 3% timing error before the
crystal.

## CRC ##
A CRC check is implemented within the Medulla firmware. The KVH 1750 uses all of the header, data, status, sequence number, and temperature in its calculation of the CRC. The following parameters are used (refer to p. 12 of the External Electrical Signaling Interface Control Document):

  * Width:       32
  * Poly:        0x04c11db7
  * Reflect In:  False
  * XOR In:      0xffffffff
  * Reflect Out: False
  * XOR Out:     0x0

CRC by Wikipedia: http://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks

CRC implementation: http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code

## MSync and TOV\_Out ##
The following are some timimg info regardless of IMU data rate:

MSync to TOV\_Out: 220 to 300 ns

TOV\_Out to IMU data transmission: 50 to 80 us

IMU data transmission (measured burst width): 388 us