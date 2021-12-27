file(GLOB core_src *.cpp)

list(APPEND CMAKE_CXX_FLAGS "-c -O3 -Wall -fPIC")
add_library(core ${core_src})