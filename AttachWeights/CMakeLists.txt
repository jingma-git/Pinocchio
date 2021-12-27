file(GLOB skin_src *.cpp)

list(APPEND CMAKE_CXX_FLAGS "-c -O3 -Wall -fPIC")
add_library(skin ${skin_src})