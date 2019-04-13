# How to setup the pyranometer for grading purposes

## What you will need
There are several pieces of hardware and software that are needed to setup the pyranometer correctly.

If you only need to compile and run the programs (not worry about all of the sensors, wireless communication, wireless power, and data upload), then you only need the following hardware:
- [Adafruit Feather M0 RFM95 LoRa Radio (900MHz)](https://www.adafruit.com/product/3178) -> You need two of these if you want hub and node running at the same time.

If you want to do a complete setup, you need all of the following:
- [Adafruit Feather M0 RFM95 LoRa Radio (900MHz)](https://www.adafruit.com/product/3178) -> Performs all computations, controls the sensors, and wirelessly sends the gathered data. Two of these are needed.
- [Adalogger FeatherWing](https://www.adafruit.com/product/2922) -> Logs gathered data to an SD card and interfaces with the multiplexer.
- OPEnS lab customer PCB board (provided by OPEnS lab) -> Allows multiple I2C sensors to be easily used with the Feather M0.
- [TCA9548A I2C Multiplexer](https://www.adafruit.com/product/2717) -> Allows the Feather M0 to use mutliple I2C sensors.
- [Adafruit TSL2591](https://www.adafruit.com/product/1980) -> Allows the capture of luminous flux of infrared and visible light.
- [TMP007 Thermopile](https://www.adafruit.com/product/2023) -> Reads the temperature of an object using its emitted infrared radiation.
- [SI1145 Light Sensor](https://www.adafruit.com/product/1777) -> Used to read UV index.
- OPEnS Lab custom multiplexer PCB.

There are a few other parts that attach to the Feather M0, but are not chips:
- [2.4GHz Dipole Swivel Antenna](https://www.adafruit.com/product/944) -> Uses to transmit data over long distances.
- [Lithium Ion Polymer Battery - 3.7v 2500mAh](https://www.adafruit.com/product/328) -> Used in conjuntion with Powerboost to power the pyranometer.
- [1 1/4'' Acrylic Dome](https://kitkraft.com/products/1-1-4-31-8mm-clear-domes) -> Used to let IR light through.
- [2'' Acrylic Dome](https://kitkraft.com/products/2-50-4mm-clear-domes) -> Used in conjunciton with the smaller dome to let IR light through.
- [Glass Sheet](https://www.goodybeads.com/store/products/A013863.htm?gclid=EAIaIQobChMI_q3O9Liq4AIVjeNkCh3AEAxFEAQYASABEgL-IPD_BwE) -> Used to let UV and visible light through. 
- Ethernet connection to the hub device.

There is also a 3D printed housing structure, but it is not neccessary to use the pyranometer, so you should no have to worry about printing it out.

In terms of software, the only changes necessary for the code is to change the mac addresses for the ethernet. Each ethernet connection will require a different set of mac addresses. The current code works for an ethernet connection in OPEnS lab. The changes should be in config.h for only the hub code.

## Installing the Arduino IDE
In order to compile the programs and flash the Feather M0, the Arduiono IDE is needed. 
- Follow the instructions [here](https://learn.adafruit.com/adafruit-feather-m0-basic-proto/setup) to install the Arduino IDE.
- Follow the instructions [here](https://learn.adafruit.com/adafruit-feather-m0-basic-proto/using-with-arduino-ide) to install the SAMD libraries.

## Setting up and running the hub
- Navigate to /LOOM/hub and open LOOM_library.ino with the Arduino IDE.
- Go to File at the top of the IDE and open up Preferences. Under "Sketchbook location", click browse. Select /LOOM/hub/LOOM_library. This lets Arduino know where to look for libraries.
- Change the mac addresses if the hub ethernet connection is not in OPEnS lab. The changes should be made in config.h of the hub code. Search for "is_ethernet" and change the values of the "byte mac[]" array.
- Plug in the Feather M0 and wait for your computer to detect/setup the device. Windows 10 does this automatically.
- Go to Tools at the top of the IDE and select "Adafruit Feather M0" as the board.
- Go to Tools at the top of the IDE and select the port the Feather M0 is connected to. 
- To compile the code, click "Verify" (circle with a checkmark) in the top left corner of the IDE.
- To flash the Feather M0 with the hub code, click "Upload" (circle with right pointing arrow) in the top left corner of the IDE.
- The hub will now be operational.

## Setting up and running the node
- Navigate to /LOOM/node and open LOOM_library.ino with the Arduino IDE.
- Go to File at the top of the IDE and open up Preferences. Under "Sketchbook location", click browse. Select /LOOM/node/LOOM_library. This lets Arduino know where to look for libraries.
- Plug in the Feather M0 and wait for your computer to detect/setup the device. Windows 10 does this automatically.
- Go to Tools at the top of the IDE and select "Adafruit Feather M0" as the board.
- Go to Tools at the top of the IDE and select the port the Feather M0 is connected to. 
- To compile the code, click "Verify" (circle with a checkmark) in the top left corner of the IDE.
- To flash the Feather M0 with the node code, click "Upload" (circle with right pointing arrow) in the top left corner of the IDE.
- The node will now be operational.

Note that the node and hub will not do a whole lot on their own. In order to see the pyrometer working as intended, you will need to wire up the sensors, connect the antennas, connect the batteries, and connect the hub to the internet.

## Making the hub operational
- Connect the antenna to the bottom of the Feather M0 that is flashed with the hub code. 
- Connect an ethernet cable to the Feather M0.
- Connect a 3.7v Lipo battery to the Feather M0.

## Making the node operational
- First, connect the Adalogger Featherwing to the Feather M0.
- Connect the OPEnS lab custom PCB to the Adalogger Featherwing.
- Connect the Adafruit multiplexer to the custom PCB.
- Connect the 3 I2C sensors (TMP007, SI1145, TSL2591) to the custom PCB.
- Connect the antenna to the bottom of the Feather M0/
- Connect a 3.7v Lipo battery to the Feather M0.

## Watching the data live
- Go to https://docs.google.com/spreadsheets/d/19apKKsIjwD41yVsG-w3Wi7nnn5LLyrmbsgc1hVF8juA/edit?usp=sharing to see the pyranometer data being uploaded in real time. If everything was hooked up properly and the hub has internet access,data should be uploaded periodically.
