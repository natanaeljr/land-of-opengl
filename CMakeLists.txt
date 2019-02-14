cmake_minimum_required(VERSION 3.5)
project(land-of-opengl LANGUAGES CXX)

#########################################################################################
# General
#########################################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DGLEW_STATIC)

#########################################################################################
# Project
#########################################################################################
set(LAND_OF_OPENGL_BIN "land-of-opengl")
set(LAND_OF_OPENGL_LIB "landofopengl")

#########################################################################################
# Includes
#########################################################################################
include(lib/glfw.cmake)
include(lib/glew.cmake)

#########################################################################################
# Headers
#########################################################################################
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)

#########################################################################################
# Sub-directories
#########################################################################################
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
