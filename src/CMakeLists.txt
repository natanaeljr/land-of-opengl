cmake_minimum_required(VERSION 3.5)

find_package(glfw3 REQUIRED PATHS ${CMAKE_BINARY_DIR}/lib NO_DEFAULT_PATH)

if(glfw3_FOUND)
    message("HDFKLDSHFALKFJALDSFJS")
endif()

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
)

#########################################################################################
# Install
#########################################################################################
install(FILES ${LAND_OF_OPENGL_BIN} DESTINATION "bin")