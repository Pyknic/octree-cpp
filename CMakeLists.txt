cmake_minimum_required(VERSION 3.5.1)

project(octree)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
