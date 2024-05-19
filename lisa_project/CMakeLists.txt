cmake_minimum_required(VERSION 3.15)
project(lisa_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Specify the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT lisa_project)

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/lib
	${CMAKE_SOURCE_DIR}/rsrc
	${CMAKE_SOURCE_DIR}/lib/wxWidgets-3.2.4/include/msvc
    ${CMAKE_SOURCE_DIR}/lib/wxWidgets-3.2.4/include
    ${CMAKE_SOURCE_DIR}/lib/wxWidgets-3.2.4/lib/vc_x64_lib
)

file(GLOB SOURCES "src/*.cpp")

add_executable(lisa_project ${SOURCES})

# Add preprocessor definitions (target-specific)
target_compile_definitions(lisa_project PRIVATE _UNICODE UNICODE)

# Link Thorlabs API
target_link_directories(lisa_project PRIVATE ${CMAKE_SOURCE_DIR}/lib/thorlabs_api)
target_link_libraries(lisa_project PRIVATE WFS_64.lib)

# Link wxWidgets
link_directories(${CMAKE_SOURCE_DIR}/lib/wxWidgets-3.2.4/lib/vc_x64_lib)
target_link_directories(lisa_project PRIVATE ${CMAKE_SOURCE_DIR}/lib/wxWidgets-3.2.4/lib/vc_x64_lib)
# Set the subsystem to "Windows"
set_target_properties(lisa_project PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Find and link OpenCV
set(OpenCV_DIR "D:/OpenCV/opencv/build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(lisa_project PRIVATE ${OpenCV_LIBS})