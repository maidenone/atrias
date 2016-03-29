# Setting up build environment #
To build firmware for the Medullas on ATRIAS an AVR GCC toolchain must be installed. On Linux this can installed using the following command:
```
sudo apt-get install gcc-avr avr-libc
```
On windows, [WinAVR](http://winavr.sourceforge.net/) can be installed to provide a standard gnu toolchain with which to compile the firmware. [Atmel Studio](http://www.atmel.com/tools/atmelstudio.aspx) can also be used to compile the firmware as it uses a standard GCC compiler, however you will need to manually setup a project to build it with.

To download the program to the Medullas you also need to install a programmer. Both Windows options (WinAVR and Atmel Studio) install programmer software that can be used. On Linux AVRDude is used to do this, and can be installed with:
```
sudo apt-get install avrdude
```

# Checking out repositories #
The firmware for ATRIAS is stored in the ATRIAS google code repository. The repository can be checked out by running:
```
git clone https://code.google.com/p/atrias/
```

In addition to the ATRIAS repository, the firmware uses hardware drivers that are stored in the Medulla Google Code repository. This repository can be checked out using:
```
svn checkout http://medulla.googlecode.com/svn/trunk/ medulla
```

# Setting up Makefile #
Once both repositories are checkout out, you need to modify the Makefile in the ATRIAS firmware directory so it can find the medulla library. To do this open the Makefile in atrias/firmware/src and change MEDULLA\_LIB\_DIR on line 16 to the relative path to the firmware/medulla\_lib directory in the medulla repository.

# Building #
Finally to build the firmware, enter the medulla/firmware/medulla\_lib directory, and run make, this will build a static library with all the firmware drivers. Then, enter the atrias/firmware/medulla\_lib directory and run make, this will build a single .hex file which can be loaded onto the medulla. Depending on the given DIP switch configuration on the Menial board, the Medulla firmware will configure it's self to whatever hardware is connected.