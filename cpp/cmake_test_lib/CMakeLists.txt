# This is the top level CMakeLists.txt file.
cmake_minimum_required(VERSION 3.6)
project(MyProj)
set(BUILD_SHARED_LIBS ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	message(STATUS "  (for debug, do cmake -DCMAKE_BUILD_TYPE=Debug)")
endif()

# Avoid using LD_LIBRARY_PATH.
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:$ORIGIN/../lib64/")

# -w to inhibit all warnings.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17 -lz")
else()
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17 -flto -lz")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(src)
add_subdirectory(bin)
