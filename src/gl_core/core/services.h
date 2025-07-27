#ifndef CORE_SERVICES_H_
#define CORE_SERVICES_H_

#include <memory>

#include "GLFW/glfw3.h"

#include "cache/material_cache.h"
#include "cache/mesh_cache.h"
#include "cache/shader_cache.h"

class Services {
    public:
        Services();
        ~Services() = default;

        const GLFWwindow* get_window() const { return m_window; }
        void set_window(GLFWwindow* window) { m_window = window; }

        float   get_width() const { return m_width; }
        void    set_width(float width) { m_width = width; }
        float   get_height() const { return m_height; }
        void    set_height(float height) { m_height = height; }
        double   get_aspect_ratio() const { return m_width/m_height; }

        float get_time() const { return m_time; }
        void set_time(float time) { m_time = time; }
        
        float get_delta() const { return m_delta; }
        void set_delta(float delta) { m_delta = delta; }

        double get_mouse_sensitivity() const { return m_mouse_sensitivity; }
        void set_mouse_sensitivity(double mouse_sensitivity) { m_mouse_sensitivity = mouse_sensitivity; }

        // coordinate transforms for rendering
        const glm::mat4& get_view() const { return m_view; }
        void set_view(const glm::mat4& view) { m_view = view; }
        const glm::mat4& get_projection() const { return m_projection; }
        void set_projection(const glm::mat4& projection) { m_projection = projection; }
        
        const std::shared_ptr<MaterialCache> &get_material_cache() const { return m_material_cache; }
        const std::shared_ptr<MeshCache> &get_mesh_cache() const { return m_mesh_cache; }
        const std::shared_ptr<ShaderCache> &get_shader_cache() const { return m_shader_cache; }

    private:

    // Object Properties
        std::shared_ptr<MaterialCache> m_material_cache;
        std::shared_ptr<MeshCache> m_mesh_cache;
        std::shared_ptr<ShaderCache> m_shader_cache;
    // Camera Data
        glm::mat4 m_view;
        glm::mat4 m_projection;
    // Context data
        GLFWwindow* m_window;
        double m_aspect_ratio;
        float m_time;
        float m_delta;
        float m_width;
        float m_height;
    // Input data

    // Settings
        double m_mouse_sensitivity = 100;

};

#endif
