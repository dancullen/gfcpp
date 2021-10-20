cmake_minimum_required(VERSION 3.14)
project(GFCPP)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)  # Allows CMake to find our custom .cmake scripts.
include(cmake/common.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  .
  deps/Catch2/single_include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(tests
  test/main.cpp
  test/MaybeTest.cpp
)

print_build_config()
