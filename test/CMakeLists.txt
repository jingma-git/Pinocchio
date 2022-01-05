cmake_minimum_required(VERSION 3.1)
project(pinocchio)


# list(APPEND CMAKE_CXX_FLAGS "-c -fPIC ")
add_subdirectory(src)

add_executable(test_basic test_basic.cpp)
target_link_libraries(test_basic my_core)

add_executable(test_mesh test_mesh.cpp)
target_link_libraries(test_mesh my_core)