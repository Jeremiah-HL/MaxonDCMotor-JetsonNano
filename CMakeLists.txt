cmake_minimum_required(VERSION 3.10)

project(Maxon)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(app ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)