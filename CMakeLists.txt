cmake_minimum_required(VERSION 3.5)
project(land-of-opengl LANGUAGES CXX VERSION 0.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#########################################################################################
# General
#########################################################################################
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -pg -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

option(LANDOFOPENGL_DOWNLOAD_DEPS OFF)

set(OpenGL_GL_PREFERENCE "GLVND")

#########################################################################################
# Project
#########################################################################################
set(LAND_OF_OPENGL_INCLUDE_DIR "include")
set(LAND_OF_OPENGL_LIBRARY "LandOfOpenGL")
set(LAND_OF_OPENGL_BINARY "land-of-opengl")

#########################################################################################
# Dependencies
#########################################################################################
find_package(OpenGL)
include(cmake/glfw3.cmake)

#########################################################################################
# Headers
#########################################################################################
include_directories(${LAND_OF_OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})

#########################################################################################
# Sub-directories
#########################################################################################
add_subdirectory(src)

#########################################################################################
# Testing
#########################################################################################
if(BUILD_TESTING)
    add_subdirectory(test)
endif(BUILD_TESTING)

#########################################################################################
# Install
#########################################################################################
install(FILES "src/${LAND_OF_OPENGL_BINARY}" DESTINATION "bin")
