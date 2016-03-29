# Setup #

## Benchtop Motor Configuration ##

  * M1 - Red
  * M2 - White
  * M3 - Black

# Details #
1. Connect

2. Expert Tuning

3. Axis Configurations
  * Single Axis
  * Rotary Motor Rotary Load
    * Single Feedback
  * Current Mode of Operation

4. Motor Setttings
  * Rotary Brushless (3 Phase)
  * Peak Current: 60 Amps (for now)
  * Continuous Stall Current: 60 Amps (for now)
  * Maximal Motor Speed: 3760 RPM
  * Pole Pairs per Revolution: 8 on benchtop, 12 in ATRIAS

5. Feedback Setttings
  * Halls Only, Port A (For trapezoidal)
  * Encoder Quad, Port A (For sinusoidal)
    * Use Digital Halls: Yes
    * Lines/Revolution: 3500

6. Current Limits
  * NA

7. Protections
  * Current Limit: 10% for 60 Amps peak, 5% for 200 Amps peak
  * Velocity Limit: 0 cnt/sec
  * Time Duration: 3000 msec

8. Inputs and Outputs
  * Touch

9. Identification
  * Delete plants if already identified
  * Hit Identify

10. Design
  * Hit Design

11. Verification
  * Hit Verify
  * Check That Waveforms Are Near Ideal

12. Commutation
  * Hit Run Commutation
  * Motor motion is positive first for A motors and negative first for B motors

13. Motion - Single Axis
  * Test Various Current Inputs
    * Current: Sine Reference
    * 10 Arms Amplitude
    * 2 Hz Frequency

14. Expert Tuning
  * Drive Save