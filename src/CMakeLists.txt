cmake_minimum_required(VERSION 3.5)

#########################################################################################
# Includes
#########################################################################################
include_directories(include)
include_directories(${GLFW_INCLUDE_DIR})

#########################################################################################
# Libraries
#########################################################################################
add_library(${LAND_OF_OPENGL_LIB} STATIC
    core.cc
)

#########################################################################################
# Executable
#########################################################################################
add_executable(${LAND_OF_OPENGL_BIN}
    main.cc
)

add_dependencies(${LAND_OF_OPENGL_BIN}
    ${LAND_OF_OPENGL_LIB}
)

target_link_libraries(${LAND_OF_OPENGL_BIN}
    ${LAND_OF_OPENGL_LIB}
    ${GLFW_LIBRARY}
    pthread
    GL
    dl
    X11
    Xrandr
    Xcursor
    Xinerama
    Xxf86vm
)

#########################################################################################
# Install
#########################################################################################
install(FILES ${LAND_OF_OPENGL_BIN} DESTINATION "bin")
