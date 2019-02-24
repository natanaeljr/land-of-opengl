/************************************************************************************************/
/**
 * \file app.cc
 * \brief Land-of-OpenGL main implementation.
 * \date 2019-02-23
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 */
/************************************************************************************************/

#include "land_of_opengl/app.h"

#include "GLFW/glfw3.h"

/************************************************************************************************/

namespace landofopengl {

int App::Launch()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        800, 600, "OpenGL", nullptr /* or glfwGetPrimaryMonitor() for fullscreen */, nullptr);

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

} /* namespace landofopengl */
