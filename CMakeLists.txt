cmake_minimum_required(VERSION 3.2)
project(Oz CXX)

add_library(oz INTERFACE)
target_include_directories(oz INTERFACE include/)

add_subdirectory(external/Catch2)

add_subdirectory(src)
