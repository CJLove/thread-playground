cmake_minimum_required(VERSION 3.12.0 )

project(thread-playground)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set (CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}
#                        ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build)

find_package(Threads REQUIRED)

add_definitions(-std=c++14)

add_subdirectory(thread)


