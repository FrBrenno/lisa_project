# Add the absolute path to the OpenCV build directory
# You may have to include the /OpenCV/opencv/build/x64/vc15/bin directory to your system PATH
set(OpenCV_DIR "C:/OpenCV/opencv-4.9.0/build")
# Add the absolute path to the wxWidgets root directory
set(wxWidgets_ROOT_DIR "C:/wxWidgets-3.2.5")

################################################################


cmake_minimum_required(VERSION 3.15)
project(lisa_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/lib
	${CMAKE_SOURCE_DIR}/rsrc
	${wxWidgets_ROOT_DIR}/include/msvc
    ${wxWidgets_ROOT_DIR}/include
)


find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(lisa_project ${SOURCES})

if(WIN32)
    # Set the subsystem to "Windows"
	set_target_properties(lisa_project PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
elseif(UNIX)
	# Set the subsystem to "Console"
	set_target_properties(lisa_project PROPERTIES LINK_FLAGS "/SUBSYSTEM:POSIX")
endif()

# Add preprocessor definitions (target-specific)
target_compile_definitions(lisa_project PRIVATE _UNICODE UNICODE)

# Link Thorlabs API
target_link_directories(lisa_project PRIVATE ${CMAKE_SOURCE_DIR}/lib/thorlabs_api)
target_link_libraries(lisa_project WFS_64.lib)

# Link wxWidgets
if(wxWidgets_FOUND)
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
    message(STATUS "Found wxWidgets ${wxWidgets_VERSION_STRING}")
else()
    message(STATUS "wxWidgets Not Found")
endif()



# Find and link OpenCV
target_link_libraries(lisa_project ${OpenCV_LIBS})
