cmake_minimum_required(VERSION 3.5)
project(land-of-opengl VERSION 0.1 LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#########################################################################################
# General
#########################################################################################
option(BUILD_DEPS "Build project dependencies" OFF)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -pg -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
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
if(BUILD_DEPS)
    message(STATUS "Building project dependencies enabled")
    set(BUILD_GLFW3 ON CACHE BOOL "")
    set(DOWNLOAD_GLAD ON CACHE BOOL "")
    set(DOWNLOAD_GSL ON CACHE BOOL "")
else()
    message(STATUS "Using project dependencies from system")
endif()

find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})

include(cmake/glfw3.cmake)
add_definitions(${GLFW3_DEFINITIONS})

include(cmake/GLAD.cmake)
add_definitions(${GLAD_DEFINITIONS})

include(cmake/GSL.cmake)
add_definitions(${GSL_DEFINITIONS})

#########################################################################################
# Headers
#########################################################################################
include_directories(${LAND_OF_OPENGL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${GLAD_INCLUDE_DIRS})
include_directories(${GSL_INCLUDE_DIRS})

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
