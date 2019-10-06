cmake_minimum_required(VERSION 3.5.1)

project(octree VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

# Compile library
file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} OBJECT ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)

# Unit Tests
enable_testing()
#add_library(test_library OBJECT test_main.cpp)

#add_executable(AABBTest test/AABBTest.cpp $<TARGET_OBJECTS:test_library>)

add_executable(AABBTest test/AABBTest.cpp $<TARGET_OBJECTS:${PROJECT_NAME}>)
target_include_directories (AABBTest PUBLIC test include)
add_test(NAME AABBTest COMMAND main)

# Move library to dist folder
set(LIBRARY_FILE lib${PROJECT_NAME}.a)
if(EXISTS ../lib/${LIBRARY_FILE})
    file(REMOVE ../lib/${LIBRARY_FILE})
endif()
file(COPY cmake-build-debug/${LIBRARY_FILE} DESTINATION ../lib)