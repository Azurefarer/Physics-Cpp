#ifndef SHADER_CLASS_SHADER_CLASS_H_
#define SHADER_CLASS_SHADER_CLASS_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "glad/glad.h"

class Shader
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        // and open them with ifstream constructor
        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);

        // Doesn't catch an empty or null path
        if (!vShaderFile || !fShaderFile) {
            std::cout << "ERROR: vshaderfile or fshaderfile failed to open" << std::endl;
        }
        else {
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            std::string vertex_code = vShaderStream.str();
            std::string fragment_code = fShaderStream.str();

            // 2. compile shaders
            // vertex shader
            unsigned int vertex = compile_shader("VERTEX", vertex_code);
            // fragment shader
            unsigned int fragment = compile_shader("FRAGMENT", fragment_code);
            if (!vertex || !fragment) {
                std::cout << "bad vert or frag" << std::endl;
            } else {
                // shader Program
                m_ID = glCreateProgram();
                if (!m_ID) {
                    std::cout << "failed to create program" << std::endl;
                } else {
                    glAttachShader(m_ID, vertex);
                    glAttachShader(m_ID, fragment);
                    glLinkProgram(m_ID);
                    if (!checkCompileErrors(m_ID, "PROGRAM")) {
                        std::cout << "program failed to link" << std::endl;
                    } else {
                        // delete the shaders as they're linked into our program now and no longer necessary
                        glDeleteShader(vertex);
                        glDeleteShader(fragment);
                        std::cout << "Shader instance success." << std::endl;
                        m_ready = true;
                    }
                }
            }
        }
    }
    // activate the shader

    void use() {
        glUseProgram(m_ID);
    }
    // utility uniform functions

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) {
        if (glGetUniformLocation(m_ID, name.c_str()) == -1) {
            m_error = true;
        } else {
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
        }
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    unsigned int id() const {
        return m_ID;
    }
    
    bool ready() const {
        return m_ready;
    }

    bool error() const {
        return m_error;
    }

private:
    unsigned int m_ID = 1;
    bool m_ready = false;
    bool m_error = false;
    void check_shader(unsigned int shader) {
        int param;
        glGetShaderiv(shader, GL_DELETE_STATUS, &param);
        if (param) {
            std::cout << "Flagged for deletion" << std::endl;
        }
        else {
            std::cout << "Not flagged for deletion" << std::endl;
        }
    }
    
    unsigned int compile_shader(std::string shader_type, const std::string& src) {
        unsigned int shader = 0;
        int success = 0;
        const char* csrc = src.c_str();
        if (shader_type == "VERTEX") {
            shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(shader, 1, &csrc, NULL);
            glCompileShader(shader);
            success = checkCompileErrors(shader, "VERTEX");
        }
        else if (shader_type == "FRAGMENT") {
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(shader, 1, &csrc, NULL);
            glCompileShader(shader);
            success = checkCompileErrors(shader, "FRAGMENT");
        } else {
            std::cout << "ERROR: unhandled shader type, " << shader_type << std::endl;
        }
        if (!success) {
            std::cout << "Shader failed to compile:" << shader_type << std::endl;
            shader = 0;
        }
        return shader;
    }
    // ------------------------------------------------------------------------
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    int checkCompileErrors(unsigned int shader, std::string type)
    {
        int success = 0;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (success == GL_FALSE)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << std::endl << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (success == GL_FALSE)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << std::endl << infoLog << std::endl;
            }
        }
        return success;
    }
};
#endif //SHADER_CLASS_SHADER_CLASS_H_
