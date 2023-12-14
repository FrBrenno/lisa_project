cmake_minimum_required(VERSION 3.12)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Set the path to the wxWidgets directory
set(wxWidgets_ROOT_DIR "path/to/wxWidgets")
set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/gcc_lib")
set(wxWidgets_CONFIGURATION mswu)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add your source files
file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the executable
add_executable(MyProject ${SOURCES})

# Link the wxWidgets libraries
target_link_libraries(MyProject ${wxWidgets_LIBRARIES})
