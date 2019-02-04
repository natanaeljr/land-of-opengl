cmake_minimum_required(VERSION 3.5)
project(land-of-opengl LANGUAGES CXX)

#########################################################################################
# General definitions
#########################################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#########################################################################################
# Project definitions
#########################################################################################
set(LAND_OF_OPENGL_BIN "land-of-opengl")
set(LAND_OF_OPENGL_LIB "landofopengl")

#########################################################################################
# Sub-directories
#########################################################################################
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
