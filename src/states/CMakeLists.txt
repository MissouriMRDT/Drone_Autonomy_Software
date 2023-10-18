cmake_minimum_required(VERSION 3.15)

# Specify your project's name
project(DroneState)

# Specify at least C++11, better C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict handling of warnings
add_definitions("-Wall -Wextra -Werror")

# Finds MAVSDK when installed system wide.
find_package(MAVSDK REQUIRED)

# Specify your app's executable name, and list of source files used to create it.
add_executable(DroneState
    DroneState.cpp
    # ... any other source files
)

# Specify your app's executable name and a list of linked libraries
target_link_libraries(DroneState
    MAVSDK::mavsdk             #All apps link against mavsdk library
    #MAVSDK::mavsdk_action      # If action plugin used by app ...
    #MAVSDK::mavsdk_telemetry   #If telemetry plugin used by app ...
    # ... Any other linked libraries
)