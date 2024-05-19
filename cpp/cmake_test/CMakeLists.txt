# This is the top level CMakeLists.txt file.

cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	message(STATUS "  (for debug, do cmake -DCMAKE_BUILD_TYPE=Debug)")
endif()

# -w to inhibit all warnings.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17 -lz")
else()
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17 -flto -lz")
endif()

add_executable(test test.cpp)
