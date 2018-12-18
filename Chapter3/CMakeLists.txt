cmake_minimum_required(VERSION 3.9)

project(Chapter3)

#message(${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/RenderLib)
link_directories(${CMAKE_SOURCE_DIR}/RenderLib)

add_compile_options(-std=c++11)
#add_library(render STATIC ${CMAKE_SOURCE_DIR}/RenderLib/render.cpp)

add_executable(chapter3.x main.cpp)
target_link_libraries(chapter3.x render)