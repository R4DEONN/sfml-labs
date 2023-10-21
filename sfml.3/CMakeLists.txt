cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-3)

include_directories(headers ../include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_INCLUDE_DIR ../include)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)


add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(031)
add_subdirectory(04)
add_subdirectory(032)
add_subdirectory(033)