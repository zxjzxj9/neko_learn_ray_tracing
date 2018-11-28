cmake_minimum_required(VERSION 3.9)

#project(RenderLib LANGUAGES C++ VERSION 0.1 DESCRIPTION library for rendering)
project(RenderLib)

add_compile_options(-std=c++11)

add_library(render STATIC render.cpp)

add_executable(test.x test.cpp)
target_link_libraries(test.x render)

