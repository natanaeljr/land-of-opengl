cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

#########################################################################################
# STB
#########################################################################################
option(DOWNLOAD_STB "Download STB library" OFF)

# Build settings
set(STB_PREFIX ${CMAKE_BINARY_DIR}/stb)
set(STBI_LIBRARY ${STB_PREFIX}/lib/libstbi.a)
set(STBI_TARGET stbi CACHE STRING "Target for add_dependencies")

# Use STB headers from system
if(NOT DOWNLOAD_STB)
    find_path(STB_INCLUDE_DIR "stb/stb_image.h")
    if (STB_INCLUDE_DIR)
        message(STATUS "Looking for STB headers: ${STB_INCLUDE_DIR} - found")
    else()
        message(STATUS "Looking for STB headers - not found")
        set(DOWNLOAD_STB ON)
    endif()
endif(NOT DOWNLOAD_STB)

# Download STB locally into the binary directory
if(DOWNLOAD_STB)
    message(STATUS "STB headers will be downloaded")
    set(STB_INCLUDE_DIR ${STB_PREFIX}/include)
    file(MAKE_DIRECTORY ${STB_INCLUDE_DIR}/stb)

    # Download and build
    ExternalProject_Add(stb
        GIT_REPOSITORY "https://github.com/nothings/stb.git"
        GIT_TAG master
        PREFIX ${STB_PREFIX}
        CONFIGURE_COMMAND ""
        UPDATE_COMMAND ""
        BUILD_COMMAND ""
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND cp stb_image.h ${STB_INCLUDE_DIR}/stb && ls -1 ${STB_INCLUDE_DIR}/stb
    )
endif(DOWNLOAD_STB)

# Create a static library for STB Image
set(STBI_SOURCE ${STB_PREFIX}/src/stb_image.cc)
add_custom_command(
    OUTPUT ${STBI_SOURCE}
    COMMAND mkdir -p src && echo \"\#define STB_IMAGE_IMPLEMENTATION 1\\n\#include \\"stb\/stb_image.h\\"\\n\" > ${STBI_SOURCE}
    WORKING_DIRECTORY ${STB_PREFIX}
    COMMENT "Generating stb_image.h implementation")
add_custom_target(stbi-generate-impl DEPENDS ${STBI_SOURCE})
set_source_files_properties(${STBI_SOURCE} PROPERTIES GENERATED TRUE)
if(DOWNLOAD_STB)
add_dependencies(stbi-generate-impl stb)
endif()

add_library(${STBI_TARGET} ${STBI_SOURCE})
add_dependencies(${STBI_TARGET} stbi-generate-impl)
target_include_directories(${STBI_TARGET}
    PUBLIC $<BUILD_INTERFACE:${STB_INCLUDE_DIR}>
    INTERFACE $<INSTALL_INTERFACE:${STB_INCLUDE_DIR}>)
set_target_properties(${STBI_TARGET} PROPERTIES
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY ${STB_PREFIX}/lib
    LIBRARY_OUTPUT_DIRECTORY ${STB_PREFIX}/lib)

# Export Variables
set(STB_INCLUDE_DIRS ${STB_INCLUDE_DIR} CACHE STRING "STB Include directories")
set(STB_LIBRARIES ${STBI_LIBRARY} CACHE STRING "STB Libraries")
set(STB_DEFINITIONS "" CACHE STRING "STB Definitions")
