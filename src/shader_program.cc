/**
 * \file shader_program.cc
 * \author Natanael Josue Rabello
 * \brief The Shader Program class definition.
 * \date 2019-03-03
 * \copyright Copyright (c) 2019
 */

#include "land_of_opengl/shader_program.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cstring>

#include <gsl/gsl>
#include "glad/glad.h"

/************************************************************************************************/

namespace landofopengl {

/************************************************************************************************/
int ShaderProgram::Create(const std::string_view vertex_path, const std::string_view fragment_path)
{
    /* Create the Vertex shader */
    std::cout << "Creating Vertex shader.." << std::endl;
    auto vertex_shader = CreateShader(ShaderType::Vertex, vertex_path);
    if (!vertex_shader.has_value()) {
        std::cerr << "Failed to create Vertex shader!" << std::endl;
        return -1;
    }
    auto _auto_delete_vertex_shader = gsl::finally([=] { glDeleteShader(*vertex_shader); });

    /* Create the Fragment shader */
    std::cout << "Creating Fragment shader.." << std::endl;
    auto fragment_shader = CreateShader(ShaderType::Fragment, fragment_path);
    if (!fragment_shader.has_value()) {
        std::cerr << "Failed to create Fragment shader!" << std::endl;
        return -1;
    }
    auto _auto_delete_fragment_shader = gsl::finally([=] { glDeleteShader(*fragment_shader); });

    /* Create the Shader Program and link */
    program_id_ = glCreateProgram();
    glAttachShader(program_id_, *vertex_shader);
    glAttachShader(program_id_, *fragment_shader);
    glLinkProgram(program_id_);

    /* Check for program linking success */
    int success = GL_FALSE;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        char info_log[1025];
        glGetProgramInfoLog(program_id_, sizeof(info_log), nullptr, info_log);
        std::cerr << "Failed to link Shader Program: " << info_log << std::endl;
        if (program_id_ != 0) {
            glDeleteProgram(program_id_);
            program_id_ = 0;
        }
        return -2;
    }

    std::cout << "Created Shader Program successfully!" << std::endl;

    return 0;
}

/************************************************************************************************/
void ShaderProgram::Delete()
{
    glDeleteProgram(program_id_);
    program_id_ = 0;
}

/************************************************************************************************/
void ShaderProgram::Use()
{
    glUseProgram(program_id_);
}

/************************************************************************************************/
std::optional<std::string> ShaderProgram::LoadFile(const std::string_view path)
{
    std::ifstream file{path.data()};

    if (!file.is_open()) {
        std::cerr << "Failed to open '" << path << "' file: " << strerror(errno) << std::endl;
        return std::nullopt;
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    file.close();

    return stream.str();
}

/************************************************************************************************/
std::optional<unsigned int> ShaderProgram::CreateShader(const ShaderType shader_type,
                                                        const std::string_view shader_path)
{
    const auto [gl_shader_type, shader_name] = [=] {
        switch (shader_type) {
            case ShaderType::Vertex:
                return std::make_tuple(GL_VERTEX_SHADER, "Vertex");
            case ShaderType::Fragment:
                return std::make_tuple(GL_FRAGMENT_SHADER, "Fragment");
        }
        return std::make_tuple(0, "(undefined)");
    }();

    /* Read shader from file */
    std::cout << "Loading " << shader_name << " shader from file.." << std::endl;
    const auto shader_source = LoadFile(shader_path);
    if (!shader_source.has_value()) {
        std::cerr << "Failed to load " << shader_name << " shader from file!" << std::endl;
        return std::nullopt;
    }

    /* Create and compile shader */
    unsigned int shader = glCreateShader(gl_shader_type);
    const char* shader_source_pointer = (*shader_source).data();
    glShaderSource(shader, 1, &shader_source_pointer, nullptr);

    std::cout << "Compiling " << shader_name << " shader.." << std::endl;
    glCompileShader(shader);

    /* Check for compilation success */
    int success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        char info_log[1024];
        glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
        if (shader != 0 && shader != GL_INVALID_ENUM) {
            glDeleteShader(shader);
        }
        std::cerr << "Failed to compile " << shader_name << " shader: " << info_log << std::endl;
        return std::nullopt;
    }

    return shader;
}

} /* namespace landofopengl */
