cmake_minimum_required(VERSION 3.1...3.15)
project(Pinocchio)

# set(CMAKE_BUILD_TYPE RELEASE)


add_subdirectory(Pinocchio)
add_subdirectory(AttachWeights)

file(GLOB src DemoUI/*.cpp)
add_executable(DemoUI ${src})
target_link_libraries(DemoUI core fltk fltk_gl GL GLU Xrender Xcursor Xfixes Xft fontconfig Xinerama pthread dl m X11)

file(GLOB src Demo/*.cpp)
add_executable(Demo ${src})
target_link_libraries(Demo core fltk fltk_gl GL GLU Xrender Xcursor Xfixes Xft fontconfig Xinerama pthread dl m X11)