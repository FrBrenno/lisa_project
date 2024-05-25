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

- Visual Studio : [Visual Studio](https://visualstudio.microsot.com/fr/downloads/) 
- NI VISA Instrument Driver : [NI VISA](https://www.ni.com/fr/support/downloads/drivers/download.ni-visa.html)
- wxWidgets : [wxWidgets](https://www.wxwidgets.org/downloads/)
- OpenCV : [OpenCV](https://opencv.org/releases/)
- CMake : [CMake](https://cmake.org/download/)

Open the CMakeLists.txt file in the folder lisa_project and set the path for both wxWidgets and OpenCV libraries :

``` CMake
# Add the absolute path to the OpenCV build directory
# You may have to include the /OpenCV/opencv/build/x64/vc15/bin directory to your system PATH
set(OpenCV_DIR "D:/OpenCV/opencv/build")
# Add the absolute path to the wxWidgets root directory
set(wxWidgets_ROOT_DIR "D:/wxWidgets-3.2.4")
```

Pay attention if the path is with slash and not backslash, otherwise cmake can not find the path.

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




