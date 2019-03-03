/**
 * \file app.cc
 * \brief Land-of-OpenGL main implementation.
 * \date 2019-02-23
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 */

#include "land_of_opengl/app.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

/************************************************************************************************/

namespace landofopengl {

/************************************************************************************************/
App::App()
{
}

/************************************************************************************************/
void App::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/************************************************************************************************/
void App::FramebufferSizeCb(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

} /* namespace landofopengl */
