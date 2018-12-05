cmake_minimum_required(VERSION 3.9)

project(RenderLib)
add_compile_options(-std=c++11)
add_library(render STATIC render.cpp vec.cpp ray.cpp geometry.cpp)
add_executable(test.x test.cpp)
target_link_libraries(test.x render)


#file(COPY ${PROJECT_BINARY_DIR}/librender.a DESTINATION ${PROJECT_SOURCE_DIR})

