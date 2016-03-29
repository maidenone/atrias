

# KVH 1750 IMU Cable #

We've ordered the same cable from two different sources: KVH and Digi-Key. The former is a [MIL-DTL](http://en.wikipedia.org/wiki/United_States_Military_Standard) cable that costs $485. The latter is a generic $29 cable.

The KVH cable does display higher build quality compared to the Digi-Key cable, though they probably aren't worth the cost right now (we aren't putting human lives on the line with ATRIAS yet).

The KVH cable:

  * Has slightly thicker (maybe 2 AWG's worth) inner conductors
  * Has a hermetic seal around the pins
  * Assigns RX/TX differential pairs to twisted conductor pairs (at 1 Mbaud UART, this probably is not a big deal, but it should help)
  * Generally fits the IMU better (<font color='red'>the Digi-Key cable has cylindrical extrusions around the mating screws that must be sawed off</font>)

## Assembly ##
Both cables have 15 conductors, but they do NOT share the same color code
mapping. Refer to <a href='http://media.digikey.com/pdf/Data%20Sheets/Norcomp%20PDFs/CCA-015-YYYR152.pdf'>this datasheet (PDF)</a>
for the Digi-Key cable.

The color mapping is as follows:

| **Pin #** | **KVH cable** | **Digi-Key cable** |
|:----------|:--------------|:-------------------|
|  1        | WHITE/BROWN   | BLACK              |
|  2        | WHITE/BLACK   | BROWN              |
|  3        | WHITE/ORANGE  | RED                |
|  4        | WHITE/YELLOW  | ORANGE             |
|  5        | BLACK         | YELLOW             |
|  6        | BROWN         | GREEN              |
|  7        | RED           | BLUE               |
|  8        | ORANGE        | VIOLET             |
|  9        | GRAY          | GRAY               |
| 10        | WHITE         | WHITE              |
| 11        | YELLOW        | PINK               |
| 12        | WHITE/GREEN   | LIGHT GREEN        |
| 13        | BLUE          | WHITE/BLACK        |
| 14        | VIOLET        | WHITE/BROWN        |
| 15        | GREEN         | WHITE/RED          |

## Pinout to Menial amplifier interface ##
| **IMU pin** | **Menial pin** | **Function** |
|:------------|:---------------|:-------------|
|  1          | 19             | IMU RS422 Transmit High |
|  2          | 20             | IMU RS422 Transmit Low |
|  3          | 22             | IMU RS422 Receive Low |
|  4          | 21             | IMU RS422 Receive High |
| 15          | 2              | Signal Ground |

## Pinout to Menial strain gauge interface ##
| **IMU pin** | **Menial pin** | **Function** |
|:------------|:---------------|:-------------|
| 11          | 4              | MSync        |

## Pinout to Menial AUX3 ##
| **IMU pin** | **Menial pin** | **Function** |
|:------------|:---------------|:-------------|
| 12          | 2              | TOV-Out      |

## Pinout to Menial 12V power ##
| **IMU pin**  | **Menial pin** | **Function** |
|:-------------|:---------------|:-------------|
|  9           | 2              | IMU Power Return |
| 10           | 1              | IMU Power Input 9-36 VDC |

## Double check! ##
Double check your cable with a multimeter. The following is a (slightly
modified) diagram of the IMU interface connector from the technical manual.
Obviously, the cable pinout is a vertical reflection of this.

![http://wiki.atrias.googlecode.com/git/kvh1750_imu_connector_loc.jpg](http://wiki.atrias.googlecode.com/git/kvh1750_imu_connector_loc.jpg)