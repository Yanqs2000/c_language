cmake_minimum_required(VERSION 3.15)
project(program)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11)
#add_executable(main ${SRC})
#add_library(calc SHARED ${SRC})
add_library(calc STATIC ${SRC})