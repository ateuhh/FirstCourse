cmake_minimum_required(VERSION 2.8)
project(Kalk)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (SOURCE_EXE Kalk.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_EXE})