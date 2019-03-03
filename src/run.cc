/************************************************************************************************/
/**
 * \file run.cc
 * \brief Land-of-OpenGL App's Run method definition.
 * \date 2019-03-02
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
const char* const App::kVertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
)";

/************************************************************************************************/
const char* const App::kFragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

/************************************************************************************************/
int App::Run()
{
    /* Initialize GLFW */
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    auto _terminate_glfw = gsl::finally([]() { glfwTerminate(); });

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

    /* Load the Vertex Shader */
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, /* count */ 1, &kVertexShaderSource, /*length*/ nullptr);
    glCompileShader(vertex_shader);
    {
        GLint success = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(vertex_shader, sizeof(info_log), nullptr, info_log);
            std::cerr << "Failed to compile Vertex Shader:\n" << info_log << std::endl;
            return -1;
        }
    }

    /* Load the Fragment Shader */
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, /*count */ 1, &kFragmentShaderSource, /*length*/ nullptr);
    glCompileShader(fragment_shader);
    {
        GLint success = 0;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(fragment_shader, sizeof(info_log), /*length*/ nullptr, info_log);
            std::cerr << "Failed to compile Fragment Shader:\n" << info_log << std::endl;
            return -1;
        }
    }

    /* Load the Shaders Program */
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    {
        GLint success = 0;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetProgramInfoLog(shader_program, sizeof(info_log), /*length*/ nullptr, info_log);
            std::cerr << "Failed to link Shader Program:\n" << info_log << std::endl;
            return -1;
        }
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    /* OpenGL drawing */
    float vertices[][3] = {
        {-0.5f, -0.5f, 0.0f},
        {+0.5f, -0.5f, 0.0f},
        {+0.0f, +0.5f, 0.0f},
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
                          /*normalized*/ GL_FALSE, /*stride*/ 3 * sizeof(float), /*pointer*/ 0);
    glEnableVertexAttribArray(/*index*/ 0);
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
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, /*first*/ 0, /*count*/ 3);

        /*************/
        /* Swap double-buffer and check for events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

} /* namespace landofopengl */
