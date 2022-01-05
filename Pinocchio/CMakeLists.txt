file(GLOB core_src *.cpp)

list(APPEND CMAKE_CXX_FLAGS "-c -fPIC") # -O3 -Wall, really make a huge difference without -O3
add_library(core ${core_src})