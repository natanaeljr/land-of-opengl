/**
 * \file run.cc
 * \brief Land-of-OpenGL App's Run method definition.
 * \date 2019-03-02
 * \author Natanael Josue Rabello
 * \copyright Copyright (c) 2019
 */

#include "land_of_opengl/app.h"

#include <iostream>

#include <gsl/gsl>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

#include "land_of_opengl/shader_program.h"

/************************************************************************************************/

namespace landofopengl {

int App::Run()
{
    /* Initialize GLFW */
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    auto _auto_terminate_glfw = gsl::finally([] { glfwTerminate(); });

    /* Create GLFW context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Mac OS X compatibility
#endif
    GLFWwindow* window = glfwCreateWindow(
        /*width*/ 800, /*height*/ 600, "Land-of-OpenGL",
        /* glfwGetPrimaryMonitor() for fullscreen */ nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &App::FramebufferSizeCb);

    /* Debug OpenGL version */
    std::cout << "OpenGL: " << glfwGetVersionString() << std::endl;

    /* Load OpenGL functions */
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Generate the Shader Program */
    ShaderProgram shader_program;
    if (int errc =
            shader_program.Create("./src/shaders/vertex.vert", "./src/shaders/fragment.frag");
        errc != 0) {
        std::cerr << "Failed to create the Shader Program (" << errc << ")!" << std::endl;
        return -1;
    }
    auto _auto_delete_shader_program = gsl::finally([&] { shader_program.Delete(); });

    /* Load the texture image */
    int width, height, nr_channels;
    unsigned char* texture_data =
        stbi_load("./res/greenwall.jpg", &width, &height, &nr_channels, 0);
    if (texture_data == nullptr) {
        std::cerr << "Failed to load texture image!" << std::endl;
        return -1;
    }
    std::cout << "Loaded 2D texture image" << std::endl;

    /* Create 2D texture */
    GLuint texture;
    glGenTextures(/*size*/ 1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, /*level*/ 0, GL_RGB, width, height, /*border*/ 0, GL_RGB,
                 GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Delete buffered image */
    stbi_image_free(texture_data);

    /* OpenGL drawing */
    float vertices[][8] = {
        { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        { +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
        { +0.0f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f },
    };

    /* Create VAO (Vertex Array Object) and VBO (Vertex Buffer Object) */
    GLuint vao, vbo;
    glGenVertexArrays(/*size*/ 1, &vao);
    glGenBuffers(/*size*/ 1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set Vertex attributes pointers
    glVertexAttribPointer(/*index*/ 0, /*size*/ 3, /*type*/ GL_FLOAT,
                          /*normalized*/ GL_FALSE, /*stride*/ 8 * sizeof(float),
                          /*pointer*/ (void*) 0);
    glEnableVertexAttribArray(/*index*/ 0);
    glVertexAttribPointer(/*index*/ 1, /*size*/ 3, /*type*/ GL_FLOAT,
                          /*normalized*/ GL_FALSE, /*stride*/ 8 * sizeof(float),
                          /*pointer*/ (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(/*index*/ 1);
    glVertexAttribPointer(/*index*/ 2, /*size*/ 2, /*type*/ GL_FLOAT,
                          /*normalized*/ GL_FALSE, /*stride*/ 8 * sizeof(float),
                          /*pointer*/ (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(/*index*/ 2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Main loop */
    while (!glfwWindowShouldClose(window)) {
        /*************/
        /* Input */
        ProcessInput(window);

        /*************/
        /* Rendering */
        glClearColor(0.2f, 0.3, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader_program.Use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, /*first*/ 0, /*count*/ 3);

        /*************/
        /* Swap double-buffer and check for events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Terminate Land-of-OpenGL." << std::endl;
    return 0;
}

} /* namespace landofopengl */
