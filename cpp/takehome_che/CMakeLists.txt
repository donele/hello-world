cmake_minimum_required(VERSION 3.19)
project(kempstarTest)

# standard build flags
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra  -Wno-unused-variable  -Wno-unused-parameter")

include_directories(include)

add_subdirectory(src)

enable_testing()
add_subdirectory (test)

add_subdirectory (benchmark)