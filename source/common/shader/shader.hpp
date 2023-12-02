#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{

    class ShaderProgram
    {

    private:
        // Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        // Constructor: Create a shader program
        ShaderProgram()
        {
            program = glCreateProgram();
        }

        // Destructor: Delete a shader program
        ~ShaderProgram()
        {
            // TODO: (Req 1) Delete a shader program
            glDeleteProgram(program);
        }

        // Attach a shader to the program based on the file and type
        bool attach(const std::string &filename, GLenum type) const;

        // Link the shader program
        bool link() const;

        // Activate the shader program for use
        void use()
        {
            glUseProgram(program);
        }

        // Get the location of a uniform variable in the shader
        GLuint getUniformLocation(const std::string &name)
        {
            // TODO: (Req 1) Return the location of the uniform with the given name
            return glGetUniformLocation(program, name.c_str());
        }

        // Set a float uniform variable in the shader
        void set(const std::string &uniform, GLfloat value)
        {
            // TODO: (Req 1) Send the given float value to the given uniform
            glUniform1f(getUniformLocation(uniform), value);
        }

        // Set an unsigned int uniform variable in the shader
        void set(const std::string &uniform, GLuint value)
        {
            // TODO: (Req 1) Send the given unsigned integer value to the given uniform
            glUniform1ui(getUniformLocation(uniform), value);
        }

        // Set an int uniform variable in the shader
        void set(const std::string &uniform, GLint value)
        {
            // TODO: (Req 1) Send the given integer value to the given uniform
            glUniform1i(getUniformLocation(uniform), value);
        }

        // Set a 2D vector uniform variable in the shader
        void set(const std::string &uniform, glm::vec2 value)
        {
            // TODO: (Req 1) Send the given 2D vector value to the given uniform
            glUniform2fv(getUniformLocation(uniform), 1, &value[0]);
            // Note: Using &value[0] is acceptable, but glm::value_ptr(value) is an alternative method
        }

        // Set a 3D vector uniform variable in the shader
        void set(const std::string &uniform, glm::vec3 value)
        {
            // TODO: (Req 1) Send the given 3D vector value to the given uniform
            glUniform3fv(getUniformLocation(uniform), 1, &value[0]);
        }

        // Set a 4D vector uniform variable in the shader
        void set(const std::string &uniform, glm::vec4 value)
        {
            // TODO: (Req 1) Send the given 4D vector value to the given uniform
            glUniform4fv(getUniformLocation(uniform), 1, &value[0]);
        }

        // Set a 4x4 matrix uniform variable in the shader
        void set(const std::string &uniform, glm::mat4 matrix)
        {
            // TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, &matrix[0][0]);
            // glUniformMatrix4fv(GLint location,GLsizei count,GLboolean transpose,const GLfloat *value);
        }

        // TODO: (Req 1) Delete the copy constructor and assignment operator.
        ShaderProgram(const ShaderProgram &) = delete;
        ShaderProgram &operator=(const ShaderProgram &) = delete;
        // Question: Why do we delete the copy constructor and assignment operator?
        // Answer: We delete them to prevent accidental copying of ShaderProgram instances,
        // ensuring that there is only one owner of the OpenGL shader program handle.
    };

}

#endif
