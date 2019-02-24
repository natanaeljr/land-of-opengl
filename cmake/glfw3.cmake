cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

#########################################################################################
# GLFW3
#########################################################################################
option(BUILD_GLFW3 "Download and build GLFW3" OFF)

# Use GLFW from system
if(NOT BUILD_GLFW3)
    find_package(glfw3 3.2.1)
    if(glfw3_FOUND)
        find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")
        find_library(GLFW3_LIBRARY "libglfw3.a")
        if (GLFW3_INCLUDE_DIR)
            message(STATUS "Looking for GLFW3 headers: ${GLFW3_INCLUDE_DIR} - found")
        else()
            message(STATUS "Looking for GLFW3 headers - not found")
            set(BUILD_GLFW3 ON)
        endif()
        if (GLFW3_LIBRARY)
            message(STATUS "Found GLFW3: ${GLFW3_LIBRARY}")
        else()
            message(STATUS "GLFW3 static library - not found")
            set(BUILD_GLFW3 ON)
        endif()
    else(glfw3_FOUND)
        message(STATUS "GLFW3 package - not found")
        set(BUILD_GLFW3 ON)
    endif(glfw3_FOUND)
endif(NOT BUILD_GLFW3)

# Build GLFW3 locally into the binary directory
if(BUILD_GLFW3)
    message(STATUS "GLFW3 will be downloaded and built")
    set(GLFW3_PREFIX ${CMAKE_BINARY_DIR}/glfw3)
    set(GLFW3_INCLUDE_DIR ${GLFW3_PREFIX}/include)
    set(GLFW3_LIBRARY ${GLFW3_PREFIX}/lib/libglfw3.a)

    # Build settings
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

    # Download and build
    ExternalProject_Add(glfw3
        URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
        PREFIX ${GLFW3_PREFIX}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${GLFW3_PREFIX}"
        UPDATE_COMMAND "")
endif(BUILD_GLFW3)

# Global Variables
set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR} CACHE STRING "GLFW3 Include directories")
set(GLFW3_LIBRARIES ${GLFW3_LIBRARY}
    X11
    Xrandr
    Xinerama
    Xxf86vm
    Xcursor
    CACHE STRING "GLFW3 Libraries"
)
set(GLFW3_DEFINITIONS -DGLFW_STATIC)
