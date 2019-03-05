cmake_minimum_required(VERSION 3.5)

#########################################################################################
# Libraries
#########################################################################################
add_library(${LAND_OF_OPENGL_LIBRARY} STATIC
    app.cc
    run.cc
    shader_program.cc
)

# Dependencies
if(GLAD_TARGET)
add_dependencies(${LAND_OF_OPENGL_LIBRARY} ${GLAD_TARGET})
endif()
if(STBI_TARGET)
add_dependencies(${LAND_OF_OPENGL_LIBRARY} ${STBI_TARGET})
endif()

target_link_libraries(${LAND_OF_OPENGL_LIBRARY}
    ${STB_LIBRARIES}
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
add_dependencies(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY})
target_link_libraries(${LAND_OF_OPENGL_BINARY} ${LAND_OF_OPENGL_LIBRARY} dl)
set_target_properties(${LAND_OF_OPENGL_BINARY} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
