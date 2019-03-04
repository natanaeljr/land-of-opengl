/**
 * \file shader_program.h
 * \author Natanael Josue Rabello
 * \brief The Shader Program class declaration.
 * \date 2019-03-03
 * \copyright Copyright (c) 2019
 */

#ifndef LAND_OF_OPENGL_SHADER_PROGRAM_H_
#define LAND_OF_OPENGL_SHADER_PROGRAM_H_

#include <string>
#include <string_view>
#include <optional>

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
     * \brief  Create the Shader Program from shader files.
     * \param  vertex_path
     * \param  fragment_path  Path to Fragment shader file.
     * \return Error code: 0 on success, other on failure.
     */
    int Create(const std::string_view vertex_path, const std::string_view fragment_path);

    /**
     * \brief  Destroy the created Shader Program.
     */
    void Delete();

    /**
     * \brief Activate this Shader Program.
     * \note  The Program must already created with Create().
     */
    void Use();

    /**
     * \brief Get the program identifier.
     * \return OpenGL shader program ID.
     */
    unsigned int GetId() const { return program_id_; }

   protected:
    /**
     * \brief  Read a shader file from the given path.
     * \param  path  Path to shader file.
     * \return Optional containing the file content as string.
     */
    std::optional<std::string> LoadFile(const std::string_view path);

    /**
     * Shader Type enumeration.
     */
    enum class ShaderType {
        Vertex,   //!< Vertex shader type
        Fragment  //!< Fragment shader type
    };

    /**
     * \brief Create a Shader in OpenGL
     * \param shader_type  The type of shader to create.
     * \param shader_path  Path to the shader file.
     * \return Optional containing the Shader ID.
     */
    std::optional<unsigned int> CreateShader(const ShaderType shader_type,
                                             const std::string_view shader_path);

   private:
    //! The program identifier in OpenGL
    unsigned int program_id_ = 0;
};

} /* namespace landofopengl */

#endif /* LAND_OF_OPENGL_SHADER_PROGRAM_H_ */
