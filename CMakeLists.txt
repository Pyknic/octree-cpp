cmake_minimum_required(VERSION 3.5.1)

project(octree)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)