#include "gl_core/shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
    std::vector<const char*> file_paths{vertex_path, fragment_path, geometry_path};
    std::vector<std::string> shader_sources(extract_from(file_paths));
    std::vector<unsigned int> compiled_shaders(compile_sources(shader_sources));
    m_ready = shader_program(compiled_shaders);
    copy_uniforms(shader_sources);
}

std::vector<std::string> Shader::extract_from(std::vector<const char*> file_path) {
    std::vector<std::string> sources;
    for (const char* path : file_path) {
        std::ifstream ShaderFile(path);
        std::stringstream ShaderStream;
        ShaderStream << ShaderFile.rdbuf();
        ShaderFile.close();
        std::string source_code = ShaderStream.str();
        sources.push_back(source_code);
    }
    return sources;
}

std::vector<unsigned int> Shader::compile_sources(std::vector<std::string> sources) {
    std::vector<unsigned int> shaders {
        compile_shader("VERTEX", sources[0]),
        compile_shader("FRAGMENT", sources[1]),
        0
    };
    if (sources[2] != "") {
        shaders[2] = compile_shader("GEOMETRY", sources[2]);
    }
    return shaders;
}

unsigned int Shader::compile_shader(std::string shader_type, std::string& src) {
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
int Shader::checkCompileErrors(unsigned int shader, std::string type)
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

bool Shader::shader_program(std::vector<unsigned int>& compiled_shaders) {
    m_ID = glCreateProgram();
    glAttachShader(m_ID, compiled_shaders[0]);
    glAttachShader(m_ID, compiled_shaders[1]);
    if (!compiled_shaders[2] == 0) {
        glAttachShader(m_ID, compiled_shaders[2]);
    }
    glLinkProgram(m_ID);
    if (!checkCompileErrors(m_ID, "PROGRAM")) {
        std::cout << "program failed to link" << std::endl;
    } else {
        glDeleteShader(compiled_shaders[0]);
        glDeleteShader(compiled_shaders[1]);
        if (!compiled_shaders[2] == 0) {
            glDeleteShader(compiled_shaders[2]);
        }
        return true;
    }
    return false;
}

void Shader::copy_uniforms(std::vector<std::string> shader_sources) {
    std::regex uniformRegex(R"(uniform\s+([a-zA-Z_][\w\d_]*)\s+([\w\d_]+)\s*;)");
    std::smatch match;
    
    for (const auto& shader_source : shader_sources) {
        std::string::const_iterator searchStart(shader_source.cbegin());
        while (std::regex_search(searchStart, shader_source.cend(), match, uniformRegex)) {
            m_uniform_names[match[2]] = match[1]; // Automatically filters duplicates
            searchStart = match.suffix().first;
        }
    }
}

void Shader::use() {
    glUseProgram(m_ID);
}

// utility uniform functions
void Shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, unsigned int value) {
    if (glGetUniformLocation(m_ID, name.c_str()) == -1) {
        m_error = true;
    } else {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }
}

void Shader::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y); 
}

void Shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z); 
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); 
}

void Shader::set_vec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w); 
}

void Shader::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
