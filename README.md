# Senior-Project-Group3-Pyranometer
Senior Project featuring the OPEnS Pyranometer radiation sensor.

# What is a pyranometer?
Pyranometers are a tool used to measure solar radiation. A typical pyranometer will gather data on the UV, IR, visible spectrum, and full spectrum solar radiation hitting the surface of the earth at a particular spot. This information could be used to help solar panel research, agricultural research, or climate change research. 

The aim of this project was to make an open-source and low-cost. To do this, this pyranometer takes more time to set up. With low-cost electronics and a 3D printer, this pyranometer can be recreated. Currently, it needs two pieces of hardware - a node and a hub. The node sends the measured data to the hub (up to 5km without building interference) where the hub uploads the data to a Google spreadsheet in live time.

# How to set up
The [Setup_Instructions_For_Grading file](https://github.com/OPEnSLab-OSU/Pyranometer/edit/master/README.md/Setup_Instructions_For_Grading.md) contains step by step instructions on what to gather and how to upload the code for this project. The Assembly_Instructions file has more in depth information on necessary materials and 3D printing instructions. In that file, the cost of each material is displayed as well as containing some basic flashing instructions.


# Description of other files and folders on this repo
The LOOM folder holds the code (using OPEnS lab LOOM 1 architecture) for the pyranometer. The node measures and reports data, while the hub is a receiver for loom and uploads data via PushingBox. The CAD folder contains files to make the 3D design. There are also folders containing documents for the Fall and Spring terms of the senior capstone class. There is also a file of informal tips for picking up the project.
