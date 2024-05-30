# PROJ-H402 Image Acquisition with Plenoptic Camera

## Table of Contents

- [PROJ-H402 Image Acquisition with Plenoptic Camera](#proj-h402-image-acquisition-with-plenoptic-camera)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Documentation](#documentation)
  - [Features](#features)
  - [Libraries](#libraries)

## Warning

Although efforts are made to keep the code documentation up-to-date, please note that it may not reflect the latest changes. Rest assured, it will be updated promptly.

## Introduction

This project, PROJ-H402 Image Acquisition with Plenoptic Camera, aims to provide a comprehensive solution for image acquisition and calibration with a plenoptic camera setup. It encompasses various functionalities, including image preprocessing, circle detection, error computation, and calibration result analysis. By leveraging the Model-View-Controller (MVC) architecture and integrating with external APIs and hardware, the software offers a versatile platform for users to calibrate micro-lens arrays and analyze captured images.

## Installation

To install the necessary libraries and software for this project, follow these steps:

1. **Visual Studio**: Download and install Visual Studio from [Visual Studio](https://visualstudio.microsoft.com/fr/downloads/).

2. **NI VISA Instrument Driver**: Install the NI VISA Instrument Driver from [NI VISA](https://www.ni.com/fr/support/downloads/drivers/download.ni-visa.html).

3. **wxWidgets**: Download and install wxWidgets from [wxWidgets](https://www.wxwidgets.org/downloads/).

4. **OpenCV**: Download and install OpenCV from [OpenCV](https://opencv.org/releases/).

5. **CMake**: Download and install CMake from [CMake](https://cmake.org/download/).

After installing the required libraries and software, open the `CMakeLists.txt` file in the `lisa_project` folder and set the paths for both wxWidgets and OpenCV libraries:

```cmake
# Add the absolute path to the OpenCV build directory
# You may have to include the /OpenCV/opencv/build/x64/vc15/bin directory to your system PATH
set(OpenCV_DIR "D:/OpenCV/opencv/build")
# Add the absolute path to the wxWidgets root directory
set(wxWidgets_ROOT_DIR "D:/wxWidgets-x.x.x")
```

Ensure that the path uses forward slashes and not backslashes.

Before compiling the program, ensure that you are using the correct API according to your hardware setup. You can switch between the WfsApi and TestApi by modifying the configuration inside the `MyApp.cpp` file. Uncomment the appropriate API instantiation and comment out the other.

 Next, open the command line in the project's root directory:

```bash
cd lisa_project/build
cmake .. && cmake --build . --config Release
```

The software executable will be created in the lisa_project/Release folder.

## Documentation

For detailed information about the project, including its architecture, algorithms used, and future work, refer to the project report located in the documentation folder.

## Features

This software offers a comprehensive set of features designed to facilitate the image acquisition and calibration process:

- **User Interface**: Intuitive user interface for seamless interaction with the software.
  
- **API Interaction**: Interact with the plenoptic camera hardware through a well-defined API.
  
- **Image Preprocessing**: Enhance image quality through various preprocessing techniques, including inversion and adaptive thresholding.
  
- **Circle Detection**: Identify micro-lens positions accurately using advanced circle detection algorithms.
  
- **Grid Generation**: Generate grid overlays on images to assist in visualizing micro-lens positions.
  
- **Error Computation**: Compute calibration errors to assess the accuracy of the calibration process.
  
- **Calibration Result Analysis**: Analyze calibration results to evaluate the quality of micro-lens manufacturing and detect potential image deformations.
  
- **Calibration Data Management**: Manage calibration data efficiently, including storage, retrieval, and analysis.
  
- **Modular Architecture**: Modular design allowing for easy integration of new features and enhancements.
  
- **Customization Options**: Customize calibration parameters and algorithms to adapt to specific use cases and hardware configurations.


## Libraries

The project utilizes the following libraries:

- **wxWidgets**: A C++ library for creating graphical user interfaces.
- **OpenCV**: An open-source computer vision and machine learning software library.
- **Eigen**: A C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
- **nlohmann\_json**: A JSON library for modern C++.
- **WFS Api**: An API for interacting with the plenoptic camera hardware.

