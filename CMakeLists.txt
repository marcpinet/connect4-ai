cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

set(CMAKE_CXX_STANDARD 20)

project(Connect4_AI)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})


add_subdirectory(lib/SFML)
include_directories(lib/SFML/include)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)