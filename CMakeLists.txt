cmake_minimum_required(VERSION 3.14)
project(enigmac)

set(CMAKE_CXX_STANDARD 14)


find_package(Boost COMPONENTS thread system REQUIRED)
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")



add_executable(enigmac main.cpp src/enigma.cpp src/enigma.h src/Sinkov.cpp src/Sinkov.h src/Crack.cpp src/Crack.h src/Settings.cpp src/Settings.h src/Result.cpp src/Result.h src/ResultContainer.cpp src/ResultContainer.h src/utils.h src/multi/multi.h src/SettingsIterator.h src/SettingsIterator.cpp  src/multi/worker_r.cpp src/multi/worker_r.h   src/multi/worker_p.cpp src/multi/worker_p.h src/multi/worker.cpp src/multi/worker.h )

add_executable(enigma_test src/enigma.cpp src/enigma.h src/Sinkov.cpp src/Sinkov.h src/Crack.cpp src/Crack.h src/Settings.cpp src/Settings.h src/Result.cpp src/Result.h src/ResultContainer.cpp src/ResultContainer.h src/utils.h src/multi/multi.h src/SettingsIterator.h src/SettingsIterator.cpp  src/multi/worker_r.cpp src/multi/worker_r.h   src/multi/worker_p.cpp src/multi/worker_p.h src/multi/worker.cpp src/multi/worker.h)

target_link_libraries(
        ${PROJECT_NAME}
        Boost::thread
)