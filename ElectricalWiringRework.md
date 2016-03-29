# Introduction #

This page contains documentation that was developed for the rework of the wiring in ATRIAS in June/July 2014.


# Details #

Detailed Layout of conductors used on ATRIAS.

| Cable # | Device Name | Connectors per Device | Devices per Leg | Wire Gauge |
|:--------|:------------|:----------------------|:----------------|:-----------|
| 1       | Incremental Encoder | 8                     | 2               | 26-28 AWG  |
| 1       | Thermistors | 7                     | 2               | 26-28 AWG  |
| 1       | Hall Effect | 5                     | 2               | 26-28 AWG  |
| 2       | Strain Gauges | 10                    | 2               | 26-28 AWG  |
| 2       | Limit Switches | 2                     | 3/4             | 26-28 AWG  |
| 3       | Motor Wires | 3                     | 2               | 12-14 AWG  |
| use existing | Absolute Encoder | 6                     | 2               | 26-28 AWG  |


Note: There are 2 additional limit switches that will be connected with their own speaker wires (a total of 4 per leg), but are not in the chart above.


Note 2: The 7 limit switches included are split up into groups of 4 and 3, depending on the leg-half they are going down.

| Cable # | Wires per leg-half|
|:--------|:------------------|
| 1       | 20 (10 pairs, braided)|
| 2       | 20 (10 pairs, braided)|
| 3       | Shielded Motor Wires |

Note: Wire 2 has two extra twisted pairs that can ''not'' be used to share Vcc and Ground because there are not enough connections on the strain board.

Wire used for Cables 1 and 2: <a href='http://www.digikey.com/product-detail/en/3600B%2F20%20100SF/MB20S-25-ND/1190684'> 20 Conductor Twisted Pair 28 AWG Wire</a> (DigiKey part no: MB20S-25-ND)
(.24in diameter)


Motor Wire used for Cable 3: <a href='http://www.wireandcabletogo.com/10-3-SEOOW-Portable-Cord-600v-Ul-CSA.html'> 10/3 SEEOW Portable Cord</a> with its insulation stripped and manually shielded (after adjustments, about .53in diameter)
Approximate cost per foot: $3.42 [breakdown](https://docs.google.com/spreadsheets/d/1_zSsgU_iPvTBpdNz14PIN9s2lwz9zyNERNnELfgPEEg/edit?usp=sharing)

Shielding: <a href='http://www.wirecare.com/product.asp?pn=WC05166143'> 3/8" Tinned Copper Braid</a>

Heat Shrink: <a href='http://www.ebay.com/itm/261189023619'>3/4" 2:1 Heat Shrink Tubing (white)</a>

Miscellaneous 2 conductor wire (logic power, limit switches, e-stop, etc.): <a href='http://www.ebay.com/itm/281083334463'>24 Gauge Red Black Speaker Wire</a>



# Wire Planning #

## Cable 1 ##

| Pair | Conductor | Solid | Band | Device | Pinout | Color on Device (if applicable) |
|:-----|:----------|:------|:-----|:-------|:-------|:--------------------------------|
| 1    | 1         | Black | Red   | Incremental Encoder | +5v    | Red                             |
| 1    | 2         | Red   | Black    | Incremental Encoder | Gnd    | Black                           |
| 2    | 3         | Black | White | Incremental Encoder | A+     | White                           |
| 2    | 4         | White | Black | Incremental Encoder | A-     | Green                           |
| 3    | 5         | Black | Green | Incremental Encoder | B+     | Yellow                          |
| 3    | 6         | Green | Black | Incremental Encoder | B-     | Brown                           |
| 4    | 7         | Black | Blue  | Incremental Encoder | Index +| Orange                          |
| 4    | 8         | Blue  | Black  | Incremental Encoder | Index -| Blue                            |
| 5    | 9         | Black |Yellow | Thermistors | Therm. 1 |                                 |
| 5    | 10        | Yellow|Black | Thermistors | Therm. 2 |                                 |
| 6    | 11        | Black |Brown | Thermistors | Therm. 3 |                                 |
| 6    | 12        | Brown |Black | Thermistors | Therm. 4 |                                 |
| 7    | 13        | Black |Orange| Thermistors | Therm. 5 |                                 |
| 7    | 14        |Orange |Black | Thermistors | Therm. 6 |                                 |
| 8    | 15        | Red   | White  | Thermistors | GND    |                                 |
| 8    | 16        | White |Red   | Hall Effect | Hall A | Brown                           |
| 9    | 17        | Red   | Green  | Hall Effect | Hall B | Orange                          |
| 9    | 18        | Green | Red  | Hall Effect | Hall C | Yellow                          |
| 10   | 19        | Red   | Blue   | Hall Effect | +5v    | Blue                            |
| 10   | 20        | Blue  | Red   | Hall Effect | GND    | Green                           |


## Cable 2 ##

| Pair | Conductor | Solid | Band | Device | Pinout / Limit Switch # |
|:-----|:----------|:------|:-----|:-------|:------------------------|
| 1    | 1         | Black | Red   | Strain Gauges | Vcc +3.3v               |
| 1    | 2         | Red   | Black    | Strain Gauges | GND                     |
| 2    | 3         | Black | White | Strain Gauges | MISO+                   |
| 2    | 4         | White | Black | Strain Gauges | MISO-                   |
| 3    | 5         | Black | Green | Strain Gauges | CLK+                    |
| 3    | 6         | Green | Black | Strain Gauges | CLK-                    |
| 4    | 7         | Black | Blue  | Strain Gauges | MOSI+                   |
| 4    | 8         | Blue  | Black  | Strain Gauges | MOSI-                   |
| 5    | 9         | Black |Yellow | Strain Gauges | CS+                     |
| 5    | 10        | Yellow|Black | Strain Gauges | CS-                     |
| 6    | 11        | Black |Brown | Limit Switch | 5, 9                    |
| 6    | 12        | Brown |Black | Limit Switch | 6, 10                   |
| 7    | 13        | Black |Orange| Limit Switch | 7, 11                   |
| 7    | 14        |Orange |Black | Limit Switch (leg half A) | 8                       |
| 8    | 15        | Red   | White  | Limit GND |  All Limit GND          |
| 8    | 16        | White |Red   | NC     |                         |
| 9    | 17        | Red   | Green  | NC     |                         |
| 9    | 18        | Green | Red  | NC     |                         |
| 10   | 19        | Red   | Blue   | NC     |                         |
| 10   | 20        | Blue  | Red   | NC     |                         |

## Flatflex Conductors ##

| Conductor | Device | Pinout | Medulla Connection (Limit Switches) |
|:----------|:-------|:-------|:------------------------------------|
| 1         | Strain Gauge | Vcc +3.3v |                                     |
| 2         | Strain Gauge | MISO+  |                                     |
| 3         | Strain Gauge | MISO-  |                                     |
| 4         | Strain Gauge | CLK+   |                                     |
| 5         | Strain Gauge | CLK-   |                                     |
| 6         | Strain Gauge | MOSI+  |                                     |
| 7         | Strain Gauge | MOSI-  |                                     |
| 8         | Strain Gauge | CS+    |                                     |
| 9         | Strain Gauge | CS-    |                                     |
| 10        | Strain Gauge | GND    |                                     |
| 11        | Limit Switch | #5, 9  |                                     |
| 12        | Limit Switch | #6, 10 |                                     |
| 13        | Limit Switch | #7, 11 |                                     |
| 14        | Limit Switch | #8     |                                     |
| 15        | GND    |        |                                     |
| 16        | GND    |        |                                     |
| 17        | GND    |        |                                     |
| 18        | GND    |        |                                     |

## Flat Flex Breakout Board Layout ##

![http://i.imgur.com/PK3qPds.png](http://i.imgur.com/PK3qPds.png)

## Limit Switches ##

Note: Begin with all the limit switches that are not running through the flat flex, number one is the rightmost top limit switch. Then 2 is the one below it, and 3 and 4 follow the same pattern below it on the left side. The rest of the limit switches move from top to bottom starting with leg half A and followed by leg half B.

Description of the first four limit switches

![http://wiki.atrias.googlecode.com/git/ElectricalWiringReworkLimitSwitches.jpg](http://wiki.atrias.googlecode.com/git/ElectricalWiringReworkLimitSwitches.jpg)

### Right Leg ###

| Switch | Function | Cable Leg (A/B) | Flatflex Conductor - LIMIT(GND) | Menial Connection (MedullaNumber) |
|:-------|:---------|:----------------|:--------------------------------|:----------------------------------|
| 1      | RA-      | N/A             | N/A                             | A1                                |
| 2      | RA+      | N/A             | N/A                             | A2                                |
| 3      | RB+      | N/A             | N/A                             | B2                                |
| 4      | RB-      | N/A             | N/A                             | B1                                |
| 5      | RLE      | B               | 11(15)                          | B5 (changed from A6)              |
| 6      | RAS-     | A               | 11(15)                          | A3                                |
| 7      | RAS+     | A               | 12(16)                          | A4                                |
| 8      | RLR      | A               | 13(17)                          | A5                                |
| 9      | RSR      | A               | 14(18)                          | A6 (changed from B5)              |
| 10     | RBS+     | B               | 12(16)                          | B4                                |
| 11     | RBS-     | B               | 13(17)                          | B3                                |

Note: Possible software fix required for right leg.

### Left Leg ###

| Switch | Function | Cable Leg (A/B) | Flatflex Conductor - LIMIT(GND) | Menial Connection (MedullaNumber) |
|:-------|:---------|:----------------|:--------------------------------|:----------------------------------|
| 1      | LA-      | N/A             | N/A                             | A1                                |
| 2      | LA+      | N/A             | N/A                             | A2                                |
| 3      | LB+      | N/A             | N/A                             | B2                                |
| 4      | LB-      | N/A             | N/A                             | B1                                |
| 5      | LLE      | B               | 11(15)                          | B5                                |
| 6      | LAS-     | A               | 11(15)                          | A3                                |
| 7      | LAS+     | A               | 12(16)                          | A4                                |
| 8      | LLR      | A               | 13(17)                          | A5                                |
| 9      | LSR      | A               | 14(18)                          | A6                                |
| 10     | LBS+     | B               | 12(16)                          | B4                                |
| 11     | LBS-     | B               | 13(17)                          | B3                                |

## Todo During Rewiring ##

  * Make Epoxy on knee look nice
  * Check/document Hall Effect Wiring colors
  * One Leg at a time
  * Clips on the Medulla (to hold wires)
  * Pictures during
  * ~~Identify limit switches~~

## Toget for Wiring ##

  * Sharpies / Electrical Tape

### Wiring Process ###

Need todo:

  * Run limit switch wire
    1. Measure & cut
    1. ? Glue wires together? [Monday](Monday.md)
    1. Solder & heatshrink to switch
    1. Heatshrink entire connection
  * Strain Gauge Wires
    1. Use ribbon cable
    1. Leave ~1ft for removal from leg
    1. Mount actual board
    1. Cut knee strain gauge wires [later](later.md)
  * Motor Wire
    1. Measure & cut
    1. Make motor wires
      * Twist all three wires
      * Label ends of now-heatshrinked wire using printable Vinyl Tape (use "Wire" format)
  * 20 Conductor
    1. Measure & cut
      * Cut past medulla
      * 20 Conductor's shield connects to the ground on the amplifier
      * Heat shrinked bundles of wires break out from there
        * Generic heatshrink until the end, then cover end with labeling heatshrink
          * Purchased heatshrink: [1](http://www.bradyid.com/bradyid/pdpv/XPS-125-1.html) & [2](http://www.bradyid.com/bradyid/pdpv/XPS-375-CONT.html)


## Final Medulla Checklist ##

### General Medulla ###

  * Power chain
  * 7 thermistor wires
  * 2 SSI Connections
  * Estop Out
  * Estop In
  * Incremental Encoder
  * Hall Effect Sensor
  * Motor Wires
  * Motor Power line

### Individual Medulla Characteristics ###

  * 6 Limits on A
  * 5 Limits on B

### Strain Gauge ###
  * RA
  * LB

### EtherCAT Order ###

Computer -> RHip -> RA -> RB -> LA -> LB -> LHip -> Boom

### EStop Order ###

RHip -> Estop Button -> RA -> RB -> LA -> LB -> Display -> LHip -> Boom -> Logic (termination)

### Power Chain ###

3 chains beginning at Display Board

  * Disp -> LHip -> RHip -> Boom
  * Disp -> RA -> RB
  * Disp -> LA -> LB

## Template(s) ##

### Template for wire pinout for MB20S-25-ND (DigiKey) 20 conductor wire ###

| Pair | Conductor | Solid | Band | Device | Pinout |
|:-----|:----------|:------|:-----|:-------|:-------|
| 1    | 1         | Black | Red   |        |        |
| 1    | 2         | Red   | Black    |        |        |
| 2    | 3         | Black | White |        |        |
| 2    | 4         | White | Black |        |        |
| 3    | 5         | Black | Green |        |        |
| 3    | 6         | Green | Black |        |        |
| 4    | 7         | Black | Blue  |        |        |
| 4    | 8         | Blue  | Black  |        |        |
| 5    | 9         | Black |Yellow |        |        |
| 5    | 10        | Yellow|Black |        |        |
| 6    | 11        | Black |Brown |        |        |
| 6    | 12        | Brown |Black |        |        |
| 7    | 13        | Black |Orange|        |        |
| 7    | 14        |Orange |Black |        |        |
| 8    | 15        | Red   | White  |        |        |
| 8    | 16        | White |Red   |        |        |
| 9    | 17        | Red   | Green  |        |        |
| 9    | 18        | Green | Red  |        |        |
| 10   | 19        | Red   | Blue   |        |        |
| 10   | 20        | Blue  | Red   |        |        |

### Strain Gauge Digitizer Pinout ###

![http://i.imgur.com/1bO8PDk.png](http://i.imgur.com/1bO8PDk.png)

What this picture shows is a top down view of the connector on the board and the sherlock connector should be built to match this. The bottom pin is incorrect, it should read GND.