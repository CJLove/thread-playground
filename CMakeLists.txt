cmake_minimum_required(VERSION 3.12.0 )

project(thread-playground)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

add_definitions(-std=c++14)

add_subdirectory(thread)


