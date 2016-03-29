

# IMU Medulla UART packet corruption issue #

The KVH 1750 IMU sends 36 bytes per packet. In order to fit this well within
our 1 ms window during 1 kHz operation, we must use 921600 baud.

This [AVR baudrate calculator (zip)](http://www.atmel.com/dyn/resources/prod_documents/AVR1307.zip)
shows that for 921600 baud, we should use the following divisors:

  * BSCALE: -7 (0x9)
  * CLK2X: 0
  * BSEL: 150 (0x96)

## Problem ##
With the above divisors, multiple Medullas have been observed to corrupt
packets from the IMU. The header and the first few following bytes are received
properly, but bytes toward the end of the packet are corrupted.

At 921600 baud, a single bit should be 1/921600 = 1.085 us wide. Sending 'U'
(0x01010101) over UART, we should be able to discern 8 bits plus the stop bit
(low), for a 9-bit wide burst: 9/921600 = 9.766 us.

Using the baudrate divisors listed above, the error should be -0.08% with a 32
MHz clock.

However, oscilloscope measurements of the width of a single bit sent by
a Medulla show otherwise. Results vary slightly between Medullas, and Brian at
Michigan says the clock drift varies by temperature, as well. Two Medullas were
tested:

Medulla 1 without external crystal:

  * Bit width 1.050 to 1.080 us
  * Burst width 9.628 to 9.668 us
    * Error -1.41% to -1.00%

Medulla 2 without external crystal:

  * Bit width 1.029 to 1.059 us
  * Burst width 9.437 to 9.476 us
    * Error -3.37% to -2.97%

Both Medullas with 16 MHz external crystal:

  * Bit width 1.062 to 1.092 us
  * Burst width 9.751 to 9.781 us
    * Error -0.15% to 0.16%

(1% error does not seem like much. I would think the UART module would
resynchronize to the stop bit at the end of every byte, for which we would need
a 50%/10 = 5% error in order to corrupt packets, but reality shows otherwise.)

It is worth noting that I was able to temporarily resolve the packet corruption
issue without the external crystal by tweaking the BSEL value to 0x99 (instead
of 0x96). This results in a bit width of 1.079 to 1.111 us and burst width
9.747 to 9.793 us, which roughly corresponds to figures resulting from using an
external crystal with the normal BSEL value.

## Solution ##
16 MHz crystal oscillator with 18 pF load capacitors attached to XTAL pins of
Medulla ATXmega.
