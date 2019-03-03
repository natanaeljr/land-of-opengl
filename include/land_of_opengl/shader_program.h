/**
 * \file shader.h
 * \author Natanael Josue Rabello
 * \brief The Shader Program class declaration.
 * \date 2019-03-03
 * \copyright Copyright (c) 2019
 */

#ifndef LAND_OF_OPENGL_SHADER_PROGRAM_H_
#define LAND_OF_OPENGL_SHADER_PROGRAM_H_

#include <tuple>
#include <string>

/************************************************************************************************/

namespace landofopengl {

/**
 * Shader Program interface for creating, loading and managing shaders.
 */
class ShaderProgram {
   public:
    /**
     * \brief Construct a new Shader Program object
     */
    ShaderProgram() = default;
    /**
     * \brief Destroy the Shader Program object
     */
    ~ShaderProgram() = default;

    /**
     * Shaders source path.
     */
    struct ShaderPath {
        std::string vertex;    //!< The Vertex shader
        std::string fragment;  //!< The Fragment shader
    };

    /**
     * \brief  Create the Shader Program for given Shader sources.
     * \param  shaders  Shaders source path.
     * \return 0 on success, other on failure.
     */
    int Create(const ShaderPath& shader_path);

    /**
     * \brief  Activate this Shader Program.
     * \return 0 on success, other on failure.
     */
    int Activate();

    /**
     * \brief Get the program identifier.
     * \return OpenGL shader program ID.
     */
    unsigned int GetId() { return id_; }

   protected:
    /**
     * \brief  Load a shader file from the given path.
     * \param  path  Path to shader file.
     * \return Tuple indicating success or failure, and the file content as string if success.
     */
    std::tuple<bool, std::string> LoadFile(const std::string& path);

   private:
    //! The program identifier in OpenGL
    unsigned int id_;
};

} /* namespace landofopengl */

#endif /* LAND_OF_OPENGL_SHADER_PROGRAM_H_ */
