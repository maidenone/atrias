# Introduction #

This page will attempt to organize and prioritize all the tasks preformed by the Medulla board. Hopefully this will help motivate a better organization for the medulla code.


# Tasks #
  * Read limit switches
  * Read encoders
  * Read thermistors
  * Read Voltages
  * Read toe switch / toe force sensor
  * Read Amp current
  * Update PWM output
  * Read Amp error signal
  * Update Ethercat bus
  * Read E-Stop input
  * Switch state machine states

# Medulla Priority #
## High Priority (>5kHz) ##
  * Read limit switches (Digital Inputs)
  * Read E-Stop (Digital Input)
  * Read Amp error signal (Digital Input)

The high priority tasks are all reading digital inputs. Therefore, I think they can all be implemented inside of interrupts directly triggered off of the inputs.


## Mid Priority (>1kHz) ##
  * Read encoders (Biss-C/SSI Synchronous)
  * Read toe switch / toe force sensor (Digital Input or Analog Input)
  * Update PWM output (Internal)
  * Update Ethercat bus (SPI Synchronous)
  * Update state machine (Internal)
  * Feed watchdog timer (Internal)

All of these tasks need to happen at least once every microsecond so that ever time the computer reads, it gets new data. These operations could run inside the main loop, as long as we can be assured that they will run fast enough. Most of them could potentially run inside some kind of timer interrupt such that they happened at a regular interval. This may be preferred because it could reduce noise in velocity measurement. At some point though, we may run into problem with having too many interrupts. At this point, I don't know how I should prioritize this, or how it should run.


## Low Priority (>500Hz) ##
  * Read thermistors (Analog Input)
  * Read voltage (Analog Input)
  * Read Amp current (RS232 Asynchronous)

The current measurement cannot run very fast, simply because the overhead in the serial protocol. The thermistor and voltage measurement just don't need to happen that often, because they shouldn't change very fast and any changes that do happen very fast are noise and we can ignore. The voltage and thermisor measurement can run inside the main event loop because we don't care about when they happen, as long as it does happen with some frequency. Current reading will be triggered by the usart interrupts since we need to do a little processing every time
we receive a byte from the amp.

# New Code Organization #
The cleanest, most efficient structure for the medulla code, I believe, would to have all inputs and outputs operate inside interrupts. This would ensure that all measurements were taken either as quickly as possible or at predefined regular intervals.

Simple digital inputs such as limit switches, toe switch, and the amp error signal could be handled as port interrupts. This would ensure that the medulla would respond to changes on the port as quickly as possible while not requiring constant monitoring of the pin by the main loop.

It should also be possible to handle SSI/Biss-C encoder inputs completely inside interrupts as well. Assuming that the encoder inputs are connected to hardware SPI ports on the xMega. This is not the case with the menial 2.0 board, this problem will be resolved in the 2.1 revision of the menial board. SPI interrupts can be used to continuously read from the encoder, when a read is completed, it will automatically kick off the next read cycle.

It is possible to have the ADC automatically cycle through any four ADC inputs on a port, updating the four result registers with the ADC value. This only partially allows autonomous operation of the ADC. By using the conversion complete interrupt, it should be possible to switch through all eight inputs on the port, thus making the ADC measurements completely autonomous from the main loop.

When there is data to be read from the Ethercat bus, the Ethercat chip conveniently generates PDI\_IRQ (Interrupt Request) signal. This interrupt request signal will generate an interrupt in the xMega that will kick off the SPI communication with the Ethercat slave chip. It is possible that we will still need to do some SPI communication with the main xMega program, to configure the Ethercat slave, but this should allow the Ethercat communication to operate automatically once configured.

To update the PWM and direction output, all that is required is to change the value of two registers. This will only need to happen when new data is received over the Ethercat bus. Thus, if the PWM and direction registers are updated inside the Ethercat IRQ interrupt, the PWM output will be updated both as quickly as possible, and only when necessary.

The only code remaining outside of the interrupt context is then the medulla state machine and the updating of the watchdog timer. It will be necessary to ensure that the watchdog timer interrupt always has a higher priority than any other interrupt than can possibly trigger. This means the interrupts for reading hardware must all be low or medium priority so they can be interrupted by the watchdog timer, or high level interrupts will have to be coded very carefully. It is probably safer to just use low and medium level interrupts for everything except the watchdog timer interrupt.