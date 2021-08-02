cmake_minimum_required(VERSION 3.12)

project(thread)

# Disable clang-tidy checks for example code
set(CMAKE_CXX_CLANG_TIDY "")

include_directories( 
    .
)

set (thread_SRC thread.cpp)

add_executable( thread ${thread_SRC})
target_link_libraries( thread pthread rt )

install(TARGETS thread DESTINATION bin)