cmake_minimum_required(VERSION 3.14)
project(enigmac)

set(CMAKE_CXX_STANDARD 14)

add_executable(enigmac main.cpp src/enigma.cpp src/enigma.h src/Sinkov.cpp src/Sinkov.h)

add_executable(enigma_test src/enigma.cpp src/enigma.h test/enigma.cpp src/Sinkov.cpp src/Sinkov.h)
