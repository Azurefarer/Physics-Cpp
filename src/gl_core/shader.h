#ifndef GL_CORE_SHADER_H_
#define GL_CORE_SHADER_H_

#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "glm/glm.hpp"
#include "glad/glad.h"

enum class GLSLtype {
    INT,
    FLOAT,

};

class Uniform {
    public:
        std::string name;
        
};

class UniformMan {
    public: 
        UniformMan(std::unordered_map<std::string, std::string> m_uniform_names);

        std::vector<std::string> m_ints;
};

class Shader {
    public:
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path = nullptr);
    private:
        std::vector<std::string> extract_from(std::vector<const char*> file_path);
        std::vector<unsigned int> compile_sources(std::vector<std::string> sources);
        unsigned int compile_shader(std::string shader_type, std::string& src);
        int checkCompileErrors(unsigned int shader, std::string type);
        bool shader_program(std::vector<unsigned int>& compiled_shaders);
        void copy_uniforms(std::vector<std::string> shader_sources);
    public:
        void use();
        void set_bool   (const std::string& name, bool value) const;
        void set_int    (const std::string& name, unsigned int value);
        void set_float  (const std::string& name, float value) const;
        void set_vec2   (const std::string &name, const glm::vec2 &value) const;
        void set_vec2   (const std::string &name, float x, float y) const;
        void set_vec3   (const std::string &name, const glm::vec3 &value) const;
        void set_vec3   (const std::string &name, float x, float y, float z) const;
        void set_vec4   (const std::string &name, const glm::vec4 &value) const;
        void set_vec4   (const std::string &name, float x, float y, float z, float w) const;
        void set_mat2   (const std::string &name, const glm::mat2 &mat) const;
        void set_mat3   (const std::string &name, const glm::mat3 &mat) const;
        void set_mat4   (const std::string &name, const glm::mat4 &mat) const;
        unsigned int id() const { return m_ID; }
        bool ready() const { return m_ready; }
        bool error() const { return m_error; }
        std::unordered_map<std::string, std::string> get_uniform_names() { return m_uniform_names; }
    private:
        unsigned int m_ID = 1;
        bool m_ready = false;
        bool m_error = false;
        std::unordered_map<std::string, std::string> m_uniform_names;
    
};

// Implement "core" shaders that every object gets a pass of to put it into the space
// Kind of a default shader
// Along with other types of basic shaders like different lighting styles
// And be able to layer these basic shader types.

#endif //SHADER_CLASS_SHADER_CLASS_H_
