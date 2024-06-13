cmake_minimum_required(VERSION 3.0)
project(job_chain)

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
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17")
else()
	set(CMAKE_CXX_FLAGS "-g -w -std=c++17 -flto")
endif()

#add_executable(chain chain.cpp)
enable_testing()
add_subdirectory(src)
add_subdirectory(benchmark)
