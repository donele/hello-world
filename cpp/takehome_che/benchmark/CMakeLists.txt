
project(kempstarTest)

include(ExternalProject)
ExternalProject_Add(
    rapidjson
    PREFIX "rapidjson"
    GIT_REPOSITORY "https://github.com/Tencent/rapidjson.git"
    GIT_TAG v1.1.0
    TIMEOUT 10
    CMAKE_ARGS
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)
ExternalProject_Get_Property(rapidjson source_dir)
set(RAPIDJSON_INCLUDE_DIR ${source_dir}/include)
include_directories(${RAPIDJSON_INCLUDE_DIR})


include(FetchContent)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.7.1
)
FetchContent_MakeAvailable(googlebenchmark)

include_directories(include)
 
add_executable (jsonRDWRBenchmark jsonRDWRBenchmark.cpp)
target_link_libraries (jsonRDWRBenchmark
	benchmark::benchmark
  Util)

add_dependencies(jsonRDWRBenchmark rapidjson)
