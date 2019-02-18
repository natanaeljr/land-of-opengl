cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

find_library(GLU_FOUND GLU)
if(NOT GLU_FOUND)
    message(FATAL_ERROR "Library dependency GLU not found!")
endif()

#########################################################################################
# GLEW
#########################################################################################
message(">> Downloading GLEW library for this build")
set(GLEW_PREFIX ${CMAKE_BINARY_DIR}/glew)
set(GLEW_INCLUDE_DIR ${GLEW_PREFIX}/include CACHE STRING "GLEW Include Directory")
set(GLEW_LIBRARY ${GLEW_PREFIX}/lib64/libGLEW.a CACHE STRING "GLEW Static Library")

# Build settings

# Download and build
ExternalProject_Add(glew
    URL "https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip"
    PREFIX ${GLEW_PREFIX}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make all
    BUILD_IN_SOURCE 1
    INSTALL_DIR ${GLEW_PREFIX}
    INSTALL_COMMAND make install GLEW_DEST=${GLEW_PREFIX}
)

