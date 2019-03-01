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
- **Total Cost** = $97.65

There are a few other parts that attach to the Feather M0, but are not chips:
- [2.4GHz Dipole Swivel Antenna](https://www.adafruit.com/product/944) -> Uses to transmit data over long distances.
- [Lithium Ion Polymer Battery - 3.7v 2500mAh](https://www.adafruit.com/product/328) -> Used in conjuntion with Powerboost to power the pyranometer.
- [1 1/4'' Acrylic Dome](https://kitkraft.com/products/1-1-4-31-8mm-clear-domes) -> Used to let IR light through.
- [2'' Acrylic Dome](https://kitkraft.com/products/2-50-4mm-clear-domes) -> Used in conjunciton with the smaller dome to let IR light through.
- [Glass Sheet](https://www.goodybeads.com/store/products/A013863.htm?gclid=EAIaIQobChMI_q3O9Liq4AIVjeNkCh3AEAxFEAQYASABEgL-IPD_BwE) -> Used to let UV and visible light through. 
- **Total Cost** = $40.25 

The last required materials are plastic for 3D printing. Depending on your 3D printer, you may need different diameter plastic:
- [Black PLA](https://www.amazon.com/SainSmart-PLA-157-PLA-Filament-Black/dp/B00AA5AJUG) -> Used to print the black-body dome.
- [White ABS](https://www.amazon.com/Octave-White-ABS-Filament-Printers/dp/B007X0QBOO) -> Used to print the housing structure.
- **Total cost** = $42

## Total cost of materials is approximately $178


