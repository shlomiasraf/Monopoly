cmake_minimum_required(VERSION 3.10)

project(monopoly)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML (adjust the path if SFML is installed in a non-standard directory)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the source files
set(SOURCES
        Board.cpp
        Card.cpp
        Square.cpp
        kindSquare.cpp
        Player.cpp
        Demo.cpp
        Monopoly.cpp
        Vertex.cpp
        Button.hpp
        Button.cpp
)

# Add the executable target
add_executable(monopoly ${SOURCES})

# Link SFML libraries
target_link_libraries(monopoly sfml-graphics sfml-window sfml-system)
