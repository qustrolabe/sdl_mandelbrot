cmake_minimum_required(VERSION 3.9)
project(sdl_mandelbrot)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} src)

add_executable(sdl_mandelbrot src/main.cpp)
target_link_libraries(sdl_mandelbrot SDL2main SDL2)
