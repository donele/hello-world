add_executable(test test.cpp)
install(TARGETS test DESTINATION bin)
target_link_libraries(test mylib)
