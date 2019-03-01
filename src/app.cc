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

#include <iostream>

#include <gsl/gsl>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

/************************************************************************************************/

namespace landofopengl {

/************************************************************************************************/
App::App() : window(nullptr)
{
}

/************************************************************************************************/
int App::Run()
{
    /* Create GLFW window */
    if (int ret = InitContext()) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return ret;
    }

    /* Load OpenGL functions */
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Main loop */
    while (!glfwWindowShouldClose(window)) {
        /* Input */
        ProcessInput(window);
        /* Rendering */
        if (int ret = RenderLoop()) {
            return ret;
        }
        /* Swap double-buffer and check for events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

/************************************************************************************************/
int App::InitContext()
{
    /* Init GLFW and create context */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X compatibility

    window = glfwCreateWindow(800, 600, "Land-of-OpenGL",
                              nullptr /* glfwGetPrimaryMonitor() for fullscreen */, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    return 0;
}

/************************************************************************************************/
void App::FinishContext()
{
    glfwTerminate();
}

/************************************************************************************************/
void App::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/************************************************************************************************/
void App::FrameBufferSizeCb(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/************************************************************************************************/
int App::RenderLoop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

} /* namespace landofopengl */
