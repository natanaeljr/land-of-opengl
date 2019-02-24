cmake_minimum_required(VERSION 3.5)

#########################################################################################
# Libraries
#########################################################################################
add_library(${LAND_OF_OPENGL_LIBRARY} STATIC
    app.cc
)

target_link_libraries(${LAND_OF_OPENGL_LIBRARY}
    ${GLFW3_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    pthread
    dl
)

#########################################################################################
# Executable
#########################################################################################
add_executable(${LAND_OF_OPENGL_BINARY} main.cc)

target_link_libraries(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY})

add_dependencies(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY})
