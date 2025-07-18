#ifndef GL_CORE_RIGIDBODY_H_
#define GL_CORE_RIGIDBODY_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>
#include <variant>

#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "gl_core/shader.h"
#include "gl_core/mesh.h"
#include "gl_core/vertex.h"


class RigidBody {
    public:
        RigidBody(const MVP& mvp);
        ~RigidBody() { --instance_count; };

        Mesh &get_mesh() const { return m_mesh; }

        void set_uniforms(const std::shared_ptr<Shader>& shader);
        void draw();
        void set_model_matrix(glm::vec3 model_offset_from_world, glm::vec3 scale = glm::vec3(1.0f));
        void update_view_and_perspective(glm::mat4 view, glm::mat4 projection);
        void set_time(float time) { m_time = time; }
        int get_instance_count() const { return instance_count; }
        std::string get_name() { return m_name; }
        void set_shader(const std::shared_ptr<Shader>& shader);
        void set_shape(std::string shape) { m_shape = shape; } //
        std::string get_shape() const { return m_shape; }
        std::shared_ptr<Shader> get_shader() const { return m_shader; }
        auto* get_uni_value(std::string uniform);
        bool gui_bool = false;
    private:
        static int instance_count;
        Mesh m_mesh;
        Material m_material;
        std::string m_name;
        MVP m_transforms;
        std::shared_ptr<Shader> m_shader;
        std::unordered_map<std::string, std::variant<int, bool, float, glm::vec2, glm::vec3, glm::vec4>> uni_values;
        glm::mat4 m_model = glm::mat4(1.0f);
        glm::mat3 m_normal = glm::mat3(1.0f);
        float m_time;
        std::string m_shape = "cube";
};

class Material {
    public:
        Material(std::shared_ptr<Shader> &shader) : m_shader(shader) {};

        void bind() const;

        void setFloat(const std::string& name, float value) { m_floats[name] = value; }
        void setVec4(const std::string& name, const glm::vec4& value) { m_vec4s[name] = value; }
        void setInt(const std::string& name, int value) { m_ints[name] = value; }
        void setMat4(const std::string& name, const glm::mat4& value) { m_mat4s[name] = value; }

    private:
        std::shared_ptr<Shader> m_shader;
        std::unordered_map<std::string, float> m_floats;
        std::unordered_map<std::string, glm::vec4> m_vec4s;
        std::unordered_map<std::string, int> m_ints;
        std::unordered_map<std::string, glm::mat4> m_mat4s;

};

#endif
