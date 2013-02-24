RaspberrySapien
===============

## Compiling in Eclipse from Windows

- Download IanLinsdell's RaspberryPi toolchain from [GitHub](https://github.com/IanLinsdell/Raspberrypi)
- Follow [these instructions](http://www.a2p.it/wordpress/tech-stuff/development/remote-debugging-raspberrypi/) to set it up

- There is an [official toolchain](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian) but I believe this only works on Linux


## RaspberryPi GPIO in C/C++

- This project uses [rpi-hw](https://github.com/Wicker25/Rpi-hw)

Another option that I have not experimented with:

- Download the [bcm2835](http://www.open.com.au/mikem/bcm2835/) library
- More details [here](http://www.raspberry-projects.com/pi/programming-in-c/compilers-and-ides/eclipse/eclipse-general-notes) and [here](http://www.raspberry-projects.com/pi/programming-in-c/c-libraries/bcm2835-by-mike-mccauley)

[WiringPi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) one is used by [Pi4J](http://pi4j.com/):
 
- Support for Gertboard, soft-servo, PiFace, I2C, SPI, Serial and mroe
- useful [diagrams](http://pi4j.com/usage.html)


## Connecting to Scratch

- First need to to right-click on a sensor block in Scratch and "enable remote sensor connections"