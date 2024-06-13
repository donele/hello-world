project(kempstarTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include_directories(include)

add_executable (xtimeTest xtimeTest.cpp)
target_link_libraries (xtimeTest
 PRIVATE
  GTest::GTest
  Util)

add_executable (xjsonTest xjsonTest.cpp)
target_link_libraries (xjsonTest
 PRIVATE
  GTest::GTest
  Util)
