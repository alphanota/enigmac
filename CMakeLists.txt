cmake_minimum_required(VERSION 3.14)
project(enigmac)

set(CMAKE_CXX_STANDARD 14)

add_executable(enigmac main.cpp src/enigma.cpp src/enigma.h src/Sinkov.cpp src/Sinkov.h src/Crack.cpp src/Crack.h src/Settings.cpp src/Settings.h src/Result.cpp src/Result.h src/ResultContainer.cpp src/ResultContainer.h)

add_executable(enigma_test src/enigma.cpp src/enigma.h test/enigma.cpp src/Sinkov.cpp src/Sinkov.h src/Settings.cpp src/Settings.h src/Crack.cpp src/Crack.h src/Result.cpp src/Result.h src/ResultContainer.cpp src/ResultContainer.h)
