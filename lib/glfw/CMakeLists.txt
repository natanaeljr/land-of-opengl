cmake_minimum_required(VERSION 3.5)

#########################################################################################
# GLFW
#########################################################################################
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include CACHE STRING "")
set(GLFW_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libglfw3.a CACHE STRING "")

# Build settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

# Download and build
ExternalProject_Add(glfw3
    URL "https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
)
