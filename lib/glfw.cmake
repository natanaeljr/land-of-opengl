cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

#########################################################################################
# GLFW
#########################################################################################
set(GLFW_PREFIX ${CMAKE_BINARY_DIR}/glfw3)
set(GLFW_INCLUDE_DIR ${GLFW_PREFIX}/include CACHE STRING "GLFW3 Include directory")
set(GLFW_LIBRARY ${GLFW_PREFIX}/lib/libglfw3.a CACHE STRING "GLFW3 Static Library")
set(GLFW_LIB_DEPENDENCIES CACHE STRING "GLFW3 Library Dependencies"
    GL
    dl
    pthread
    X11
    Xrandr
    Xcursor
    Xinerama
)

# Build settings
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

# Download and build
ExternalProject_Add(glfw3
    URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
    PREFIX ${GLFW_PREFIX}
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${GLFW_PREFIX}"
)
