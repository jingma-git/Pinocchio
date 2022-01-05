file(GLOB skin_src *.cpp)

list(APPEND CMAKE_CXX_FLAGS "-c -fPIC") # -O3 -Wall
add_library(skin ${skin_src})