#ifndef CORE_SERVICES_H_
#define CORE_SERVICES_H_

#define GLFW_INCLUDE_NONE

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>

#include "GLFW/glfw3.h"

#include "cache/material_cache.h"
#include "cache/mesh_cache.h"
#include "cache/shader_cache.h"
#include "core/types.h"

class Services {
    public:
    Services();
    ~Services() = default;
    
    void config_cache();

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
    
    bool get_free_cursor() const { return m_free_cursor; }
    void set_free_cursor(bool freedom) { m_free_cursor = freedom; }
    // Input
    const keys& get_keys() { return m_keys; }
    void set_keys(keys keys) { m_keys = keys; }
    
    double get_cursor_diff_x() { return m_cursor_diff_x; }
    void set_cursor_diff_x(double x) { m_cursor_diff_x = x; }
    double get_cursor_diff_y() { return m_cursor_diff_y; }
    void set_cursor_diff_y(double y) { m_cursor_diff_y = y; }
    
    double get_cursor_pos_x() { return m_cursor_pos_x; }
    void set_cursor_pos_x(double x) { m_cursor_pos_x = x; }
    double get_cursor_pos_y() { return m_cursor_pos_y; }
    void set_cursor_pos_y(double y) { m_cursor_pos_y = y; }
    
    double get_scroll_offset_x() { return m_scroll_offset_x; }
    void set_scroll_offset_x(double x) { m_scroll_offset_x = x; }
    double get_scroll_offset_y() { return m_scroll_offset_y; }
    void set_scroll_offset_y(double y) { m_scroll_offset_y = y; }
    
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
        double m_aspect_ratio;
        float m_time;
        float m_delta;
        float m_width;
        float m_height;
        bool m_free_cursor;
    // Input data
        keys m_keys;
        double m_cursor_diff_x = 0.0f;
        double m_cursor_diff_y = 0.0f;
        double m_cursor_pos_x;
        double m_cursor_pos_y;
        double m_scroll_offset_x = 0.0f;
        double m_scroll_offset_y = 0.0f;
    // Settings
        double m_mouse_sensitivity = 100;
};

struct scene_data {

    // Everything in this struct should be able to be categorized as a System

    // *Sys* Resolution tracking
    struct Resolution {
        int WIDTH = 2560;
        int HEIGHT = 1440;
    };
    Resolution res;

    // int counting system
    int rigidbodies = 0;

    // Shader Texture System
    bool set_null = false;
    bool set_king = false;
    bool set_face = false;
    bool set_back = false;
    bool set_sand = false;

    // Shader uniform system
    float v_amplitude_mult = 1.050;
    float v_amplitude = 2.150;
    float v_omega_mult = 0.440;
    float v_omega = 0.02;
    float v_lambda_mult = 1.500;
    float v_lambda = 326.000; // 320
    float v_peak_width = 0.430;
    float fresnel_coeff = 10.0;
    float spec_coeff = 7.0;

    bool toon = true;
    int toon_buckets = 8;

    float ambient_strength = 1.0;
    glm::vec4 light_color = glm::vec4{1.0};
    glm::vec4 light_pos = glm::vec4{0.0, 0.0, 0.0, 0.0};
};

struct batch_data {

    // Same with the Batch data, everything should be a part of a system.

    glm::vec3 pos = glm::vec3(0.0, -100.0, 0.0);
    float width = 500.0f;
    float length = 500.0f;
    float subdivide_width = 5.0f;
    float subdivide_length = 5.0f;

    int draw_count = 0;
    int quad_count = 0;
};

#endif
