project(kempstarTest)

set(UTIL_SRC
	xtime.cpp
	xjson.cpp
        )

add_library(Util STATIC ${UTIL_SRC})
target_include_directories(Util PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable (timerEvent timerEvent.cpp)
target_link_libraries (timerEvent Util)
