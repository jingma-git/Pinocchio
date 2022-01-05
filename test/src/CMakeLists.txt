file(GLOB SRC *.cpp)

# list(APPEND CMAKE_CXX_FLAGS "-c -fPIC") # -O3 -Wall
add_library(my_core ${SRC})