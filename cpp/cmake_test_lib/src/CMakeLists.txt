set(LIBNAME mylib)
set(SOURCES mylib.cpp)
add_library(${LIBNAME} ${SOURCES})
install(TARGETS ${LIBNAME} DESTINATION lib64)
