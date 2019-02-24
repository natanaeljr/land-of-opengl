cmake_minimum_required(VERSION 3.5)

#########################################################################################
# Libraries
#########################################################################################
add_library(${LAND_OF_OPENGL_LIBRARY} STATIC
    app.cc
)

target_link_libraries(${LAND_OF_OPENGL_LIBRARY}
    ${GLAD_LIBRARIES}
    ${GLFW3_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    dl
    pthread
)

#########################################################################################
# Executable
#########################################################################################
add_executable(${LAND_OF_OPENGL_BINARY} main.cc)

target_link_libraries(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY} dl)

add_dependencies(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY})
