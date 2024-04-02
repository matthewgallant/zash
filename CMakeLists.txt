# Zash
# A wicked fast command-line text editor written in pure C.
# (c) 2024 Matthew Gallant

cmake_minimum_required(VERSION 3.05)
project(zash VERSION 1.0)

# Configure compiler
add_definitions(-std=c99)
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

# Find libraries
find_package(Curses REQUIRED)

# Include sources & includes
file(GLOB SOURCES src/*.c)
set(INCLUDES include/)

# Entry point
add_executable(zash ${SOURCES})

# Link includes
target_link_libraries(zash ${CURSES_LIBRARIES})
target_include_directories(zash PRIVATE ${INCLUDES})
