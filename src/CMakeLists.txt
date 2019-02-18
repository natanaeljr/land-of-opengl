cmake_minimum_required(VERSION 3.5)

#########################################################################################
# Libraries
#########################################################################################
add_library(${LAND_OF_OPENGL_LIB} STATIC
    core.cc
)

target_link_libraries(${LAND_OF_OPENGL_LIB}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    pthread
    dl
    X11
    Xrandr
    Xcursor
    Xinerama
    Xxf86vm
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
)

#########################################################################################
# Install
#########################################################################################
install(FILES ${LAND_OF_OPENGL_BIN} DESTINATION "bin")
