#include "asset/material.h"

void Material::use_shader() {
    m_shader->use();
}

// You must use the shader before setting its uniforms
void Material::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_shader->get_id(), name.c_str()), (int)value);
}

void Material::set_int(const std::string& name, unsigned int value) {
    glUniform1i(glGetUniformLocation(m_shader->get_id(), name.c_str()), value);
}

void Material::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_shader->get_id(), name.c_str()), value);
}

void Material::set_vec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, &value[0]); 
}

void Material::set_vec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(m_shader->get_id(), name.c_str()), x, y); 
}

void Material::set_vec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, &value[0]); 
}

void Material::set_vec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(m_shader->get_id(), name.c_str()), x, y, z); 
}

void Material::set_vec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, &value[0]); 
}

void Material::set_vec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(m_shader->get_id(), name.c_str()), x, y, z, w); 
}

void Material::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Material::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->get_id(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// void MaterialCache::set_shader_uniform_texture(const std::string& tex_name, const std::string& uniform) {
//     auto tex_int = m_texture_man->get_tex_int(tex_name.c_str());
//     if (!tex_int.has_value()) {
//         throw std::runtime_error("invalid tex");
//     }
//     for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
//         auto material = it->second;
//         material->use();
//         material->set_int(uniform, tex_int.value());
//     }
// }
