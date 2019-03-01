# How to operate and assemble the OPEnS Lab Pyranometer

## Gathering materials
All materials for the OPEnS lab pyranometer can be found below. Substitutions can only be made where specified.

There are several chips that are needed, and they are as follows:
- [Adafruit Feather M0 RFM95 LoRa Radio (900MHz)](https://www.adafruit.com/product/3178) -> Performs all computations, controls the sensors, and wirelessly sends the gathered data.
- [Adalogger FeatherWing](https://www.adafruit.com/product/2922) -> Logs gathered data to an SD card and interfaces with the multiplexer.
- OPEnS lab customer PCB board (provided by OPEnS lab) -> Allows multiple I2C sensors to be easily used with the Feather M0.
- [TCA9548A I2C Multiplexer](https://www.adafruit.com/product/2717) -> Allows the Feather M0 to use mutliple I2C sensors.
- [Adafruit TSL2591](https://www.adafruit.com/product/1980) -> Allows the capture of luminous flux of infrared and visible light.
- [TMP007 Thermopile](https://www.adafruit.com/product/2023) -> Reads the temperature of an object using its emitted infrared radiation.
- [SI1145 Light Sensor](https://www.adafruit.com/product/1777) -> Used to read UV index.
- [PowerBoost 500 Charger](https://www.adafruit.com/product/1944) -> Used to boost 3.7v to 5.2v.
- **Note that all of these chips need to be soldered**
- **Total Cost = $97.65**

There are a few other parts that attach to the Feather M0, but are not chips:
- [2.4GHz Dipole Swivel Antenna](https://www.adafruit.com/product/944) -> Uses to transmit data over long distances.
- [Lithium Ion Polymer Battery - 3.7v 2500mAh](https://www.adafruit.com/product/328) -> Used in conjuntion with Powerboost to power the pyranometer.
- [1 1/4'' Acrylic Dome](https://kitkraft.com/products/1-1-4-31-8mm-clear-domes) -> Used to let IR light through.
- [2'' Acrylic Dome](https://kitkraft.com/products/2-50-4mm-clear-domes) -> Used in conjunciton with the smaller dome to let IR light through.
- [Glass Sheet](https://www.goodybeads.com/store/products/A013863.htm?gclid=EAIaIQobChMI_q3O9Liq4AIVjeNkCh3AEAxFEAQYASABEgL-IPD_BwE) -> Used to let UV and visible light through. 
- **Total Cost = $40.25**

The last required materials are plastic for 3D printing. Depending on your 3D printer, you may need different diameter plastic:
- [Black PLA](https://www.amazon.com/SainSmart-PLA-157-PLA-Filament-Black/dp/B00AA5AJUG) -> Used to print the black-body dome.
- [White ABS](https://www.amazon.com/Octave-White-ABS-Filament-Printers/dp/B007X0QBOO) -> Used to print the housing structure.
- **Total cost = $42**

**Total cost of materials is approximately $178**

## Printing the Structure and Black-Body Dome
The entire structure, save for the glass and acrylic, is 3D printed. The project consists of 3 different prints: the lid, the main container, and the black-body dome. The total time of printing everything is about 18 hours. It is recommended to first print the lid, then print the main container over night, and print the black-body dome last. Instructions on how to print the objects will vary depending on the printer and slicing software being used, but below are general instructions:

**Printing the Lid**

- Download the lid CAD design found in this repo at /CAD/lid.stl.
- Load lid.stl into your slicing software.
- Orient the lid such that the top of the lid is touching the bed of the 3D printer. The sides of the lid should be on top.
- Select ABS as the material being used.
- Select standard level of detail with 30% infill.
- Add brim to go around the base of the object.
- DO NOT ADD SUPPORT -> Support may cause problems with latching the lid to the main container.
- Slice the object and generate a .gcode file.
- Load the white ABS filament into your 3D printer.
- Load your .gcode file into the 3D printer.
- Spray an even layer of hairspray on the bed.
- Start the print.
- Watch the first couple layers and make sure the plastic layers are not peeling off the bed.
- Once the print job is complete, use a paint scraper to carefully pry the lid from the bed.
- **Total Print Time = 5-7 hours**

**Printing the Main Container**

- Download the lid CAD design found in this repo at /CAD/main_container.stl.
- Load main_container.stl into your slicing software.
- Orient the main container such that is is upright, as in the floor of the container is against the 3D printer bed.
- Select ABS as the material being used.
- Select standard level of detail with 30% infill.
- Add brim to go around the base of the object.
- DO NOT ADD SUPPORT -> Support may cause problems with latching the lid to the main container.
- Slice the object and generate a .gcode file.
- Load the white ABS filament into your 3D printer.
- Load your .gcode file into the 3D printer.
- Spray an even layer of hairspray on the bed.
- Start the print.
- Watch the first couple layers and make sure the plastic layers are not peeling off the bed.
- Once the print job is complete, use a paint scraper to carefully pry the lid from the bed.
- **Total Print Time = 9-12 hours**

**Printing the Black-Body Dome**

- Download the lid CAD design found in this repo at /CAD/dome.stl.
- Load dome.stl into your slicing software.
- Orient the dome such that is is upright, as in the object looks like an upside-down bowl.
- Select PLA as the material being used.
- Select standard level of detail with 30% infill.
- Add brim to go around the base of the object.
- DO NOT ADD SUPPORT -> Removing the support is exceedingly difficult and is not needed.
- Slice the object and generate a .gcode file.
- Load the black PLA filament into your 3D printer.
- Load your .gcode file into the 3D printer.
- Spray an even layer of hairspray on the bed.
- Start the print.
- Watch the first couple layers and make sure the plastic layers are not peeling off the bed.
- Once the print job is complete, use a paint scraper to carefully pry the lid from the bed.
- Once done, use a scale to measure the mass of the dome in kilograms and take note of it. The mass will be used later when calculating total W/m^2.
- **Total Print Time = 20-30 minutes**

Make sure the objects are sturdy and are not warped. The lid should latch onto the top of the main container with only a small amount of effort. Be careful not to crack the outer wall of the main container; be gentle!

## Flashing the Feather M0
The Feather M0 needs to have the LOOM software loaded onto it in order for it to function. The following instructions will help ensure the Feather M0 is ready to begin controlling the pyranometer:

- Follow the instructions [here](https://learn.adafruit.com/adafruit-feather-m0-basic-proto/setup) to install the Arduino IDE.
- Follow the instructions [here](https://learn.adafruit.com/adafruit-feather-m0-basic-proto/using-with-arduino-ide) to install the proper libraries.
- Download the folder /LOOM/node and save it to a convenient location.
- Navigate to the folder and open /node/LOOM_library.ino.
- In the top left folder click "File"->"Preferences".
- Change the sketch location to be the file path to LOOM_library.
- Navigate to the file /LOOM_library/loom_tmp007.h
- search for the term "double mass".
- On the right hand side of the equal side, change the value to the exact mass of the black-body dome in kilograms.
- Save the file.
- Connect the Feather M0 to your computer using a USB/USB-C cable. 
- In the top left corner click the "upload button" (it looks like an arrow pointing right).
- If the terminal at the bottom reports no errors and says "CPU reset successfully" as the last message, the Feather M0 was successfully flashed.
- Disconnect the Feather M0, note that the LOOM software remains in the Feather M0 and will restart each time the Feather M0 is powered on.


