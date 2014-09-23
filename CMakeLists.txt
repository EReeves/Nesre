cmake_minimum_required(VERSION 2.8.4)
project(nesre)

set(SOURCE_FILES CPU/registers.h CPU/registers.cpp CPU/cpu.h CPU/cpu.cpp main.cpp)
add_executable(nesre ${SOURCE_FILES})