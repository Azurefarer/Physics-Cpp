#ifndef GL_CORE_SHADER_H_
#define GL_CORE_SHADER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "glm/glm.hpp"
#include "glad/glad.h"

class Shader
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
        // 1. retrieve the vertex/fragment source code from filePath
        // and open them with ifstream constructor
        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);
        std::ifstream gShaderFile(geometryPath);

        // Doesn't catch an empty or null path
        if (!vShaderFile || !fShaderFile) {
            std::cout << "ERROR: vshaderfile or fshaderfile failed to open" << std::endl;
        } else {
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            if (!vShaderStream || !fShaderStream) {
                std::cout << "ERROR: vshaderstream or fshaderstream is empty" << std::endl;
            } else {
                vShaderFile.close();
                fShaderFile.close();
                std::string vertex_code = vShaderStream.str();
                std::string fragment_code = fShaderStream.str();
                std::string geometry_code;
                if ( geometryPath != nullptr ) {
                    gShaderFile.open(geometryPath);
                    std::stringstream gShaderStream;
                    gShaderStream << gShaderFile.rdbuf();
                    gShaderFile.close();
                    geometry_code = gShaderStream.str();
                }
                // 2. compile shaders
                unsigned int vertex = compile_shader("VERTEX", vertex_code);
                unsigned int fragment = compile_shader("FRAGMENT", fragment_code);
                unsigned int geometry;
                if ( geometryPath != nullptr ) {
                    geometry = compile_shader("GEOMETRY", geometry_code);
                    const char * gShaderCode = geometry_code.c_str();
                    geometry = glCreateShader(GL_GEOMETRY_SHADER);
                    glShaderSource(geometry, 1, &gShaderCode, NULL);
                    glCompileShader(geometry);
                    checkCompileErrors(geometry, "GEOMETRY");
                }
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
                            if (geometryPath != nullptr) { glDeleteShader(geometry); }
                            m_ready = true;
                        }
                    }
                }
            }
        }
    const auto ready_01 = ready();
    if (!ready_01) {
        std::cout << "ready : " << ready_01 << std::endl;
    }
    }
    // activate the shader

    void program_number() {
        glValidateProgram(m_ID);
        int param;
        glGetProgramiv(m_ID, GL_VALIDATE_STATUS, &param);
        std::cout << param << std::endl;
    }

    void use() {
        glUseProgram(m_ID);
    }
    // utility uniform functions

    void set_bool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void set_int(const std::string& name, unsigned int value) {
        if (glGetUniformLocation(m_ID, name.c_str()) == -1) {
            m_error = true;
        } else {
            glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
        }
    }

    void set_float(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void set_vec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void set_vec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void set_vec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void set_vec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void set_vec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
    }
    void set_vec4(const std::string &name, float x, float y, float z, float w) const
    { 
        glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void set_mat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void set_mat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void set_mat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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
        GLuint shader = 0;
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
        }
        else if (shader_type == "GEOMETRY") {
            shader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(shader, 1, &csrc, NULL);
            glCompileShader(shader);
            success = checkCompileErrors(shader, "GEOMETRY");
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
