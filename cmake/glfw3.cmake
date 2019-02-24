cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

#########################################################################################
# GLFW
#########################################################################################
if(LANDOFOPENGL_DOWNLOAD_DEPS)
    set(BUILD_GLFW3 ON)
else()
    find_package(glfw3)
    if(glfw3_FOUND)
        message("-- Found GLFW3 cmake package")
        find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")
        find_library(GLFW3_LIBRARY "libglfw3.a")
        if (GLFW3_INCLUDE_DIR)
            message("-- Looking for GLFW/glfw3.h - found")
        else()
            message("-- Looking for GLFW/glfw3.h - not found")
            set(BUILD_GLFW3 ON)
        endif()
        if (GLFW3_LIBRARY)
            message("-- Looking for libglfw3.a - found")
        else()
            message("-- Looking for libglfw3.a - not found")
            set(BUILD_GLFW3 ON)
        endif()
    else(glfw3_FOUND)
        message("-- GLFW3 package - not found")
        set(BUILD_GLFW3 ON)
    endif(glfw3_FOUND)
endif(LANDOFOPENGL_DOWNLOAD_DEPS)


# Build GLFW3 locally into the binary directory
if(BUILD_GLFW3)
    message("-- GLFW3 will be downloaded and built")
    set(GLFW3_PREFIX ${CMAKE_BINARY_DIR}/glfw3)
    set(GLFW3_INCLUDE_DIR ${GLFW3_PREFIX}/include)
    set(GLFW3_LIBRARY ${GLFW3_PREFIX}/lib/libglfw3.a)

    # Build settings
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_EXAMPLES OFF)

    # Download and build
    ExternalProject_Add(glfw3
        URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
        PREFIX ${GLFW3_PREFIX}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${GLFW3_PREFIX}"
        UPDATE_COMMAND ""
    )
endif(BUILD_GLFW3)

# Global Variables
set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR} CACHE STRING "GLFW3 Include directories")
set(GLFW3_LIBRARIES ${GLFW3_LIBRARY}
    X11
    Xrandr
    Xcursor
    Xinerama
    Xxf86vm
    CACHE STRING "GLFW3 Libraries"
)
