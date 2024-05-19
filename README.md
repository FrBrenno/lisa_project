# PROJ-H402 Image Acquisition with Plenoptic Camera

## Table of Contents

- [PROJ-H402 Image Acquisition with Plenoptic Camera](#proj-h402-image-acquisition-with-plenoptic-camera)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Features](#features)
  - [Librairies](#librairies)

## Introduction

## Installation

User should install the following libraries and softwares:
- Thorlabs Wavefront Sensor : [WFS](https://www.thorlabs.com/newgrouppage9.cfm?objectgroup_id=5287&tabname=Software)
  - Needed to be installed, so we can get all the drivers needed.
- wxWidgets : [wxWidgets](https://www.wxwidgets.org/downloads/)
- OpenCV : [OpenCV](https://opencv.org/releases/)
- CMake : [CMake](https://cmake.org/download/)

Open the CMakeLists.txt file in the folder lisa_project and set the path for both wxWidgets and OpenCV libraries.

Open the command line on the root:
```bash
cd lisa_project/build
cmake .. && cmake --build . --config Release
```

The software executable will be created in the folder `lisa_project/Release`.

## Features



## Librairies

- wxWidgets
- OpenCV
- Eigen
- nlohmann_json
- WFS Api




