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

/************************************************************************************************/

namespace landofopengl {

/************************************************************************************************/
int ShaderProgram::Create(const ShaderPath& shader_path)
{
    bool success;
    std::string vertex_shader;
    std::tie(success, vertex_shader) = LoadFile(shader_path.vertex);
    if (!success) {
        std::cerr << "Failed to load the vertex shader!" << std::endl;
        return -1;
    }

    return 0;
}

/************************************************************************************************/
int ShaderProgram::Activate()
{
    return 0;
}

/************************************************************************************************/
std::tuple<bool, std::string> ShaderProgram::LoadFile(const std::string& path)
{
    std::ifstream file{path};

    if (!file.is_open()) {
        std::cerr << "Failed to open '" << path << "' file!" << std::endl;
        return {false, {}};
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    file.close();

    return {true, stream.str()};
}

} /* namespace landofopengl */
