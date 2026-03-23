cmake_minimum_required(VERSION 3.16)

project(breakout VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Add Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Add subdirectories
add_subdirectory(src)
