cmake_minimum_required(VERSION 3.5)
project(filemonitor)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(filemonitor main.cpp)

target_link_libraries(filemonitor Qt5::Core)