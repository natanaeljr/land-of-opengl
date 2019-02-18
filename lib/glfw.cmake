cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

#########################################################################################
# GLFW
#########################################################################################
find_package(glfw3 QUIET)

if(glfw3_FOUND)
    message("Using GLFW3 library from system")
    set(GLFW_INCLUDE_DIR include CACHE STRING "GLFW3 Include directory")
    set(GLFW_LIBRARY glfw CACHE STRING "GLFW3 Static Library")

else(glfw3_FOUND)
    message("Downloading GLFW3 library for this build")
    set(GLFW_PREFIX ${CMAKE_BINARY_DIR}/glfw3)
    set(GLFW_INCLUDE_DIR ${GLFW_PREFIX}/include CACHE STRING "GLFW3 Include directory")
    set(GLFW_LIBRARY ${GLFW_PREFIX}/lib/libglfw3.a CACHE STRING "GLFW3 Static Library")

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

endif(glfw3_FOUND)
