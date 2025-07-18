#include "gl_core/renderer.h"

Renderer::Renderer(const std::shared_ptr<Services>& pservices) : m_services(pservices) {
    m_assets = std::make_shared<std::vector<std::shared_ptr<RigidBody>>>();
    m_batch = std::make_unique<BatchRenderer>();
    m_texture_man = std::make_unique<TextureMan>();
    set_MVP(glm::vec3(0.0), glm::vec3(1.0f));
    rigidbody_push_back(m_transforms);
    rigidbody_push_back(m_transforms);
    set_shader_uniform_texture("NULL", "texture01");
    update_gui_uniforms();
    std::shared_ptr<Shader> shader_ref = ShaderCache::get_instance().m_shader_programs["point_light"];
    (*m_assets)[0]->set_shader(shader_ref);
}


void Renderer::run() {
    process_delta();
    draw();
    gui_updates();
    context_updates();
}

void Renderer::render(const Scene& scene) {
    const auto& bodies = scene.get_rigid_bodies();

    for (const auto& body : bodies) {
        shader.setMat4("u_Model", body->m_transform);
        body->m_mesh->bind();
        glDrawElements(GL_TRIANGLES, body->m_mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
    }
}

void Renderer::draw() {
    MVP temp = m_context->get_MVP();

    for (auto& asset : *m_assets) {
        asset->update_view_and_perspective(temp.view, temp.projection);
        asset->set_time(m_current_frame);
        if (asset->get_shape() == "BATCH") {
            draw_batch();
        } else {
            asset->draw();
        }
    }
}

void Renderer::rigidbody_push_back(const MVP& mvp) {
    (*m_assets).push_back(std::make_shared<RigidBody>(mvp));
    m_gui->set_rigidbodies(m_assets);
    m_sdata.rigidbodies = (*m_assets)[0]->get_instance_count();
}

void Renderer::set_MVP(glm::vec3 model_offset, glm::vec3 scale) {
    m_transforms = m_context->get_MVP();
    glm::mat4 model(1.0f);
    model = glm::translate(model, model_offset);
    model = glm::scale(model, scale);
    m_transforms.model = model;
}

void Renderer::update_gui_uniforms() {
    m_sdata = m_gui->get_scene_data();
    m_bdata = m_gui->get_batch_data();
}

void Renderer::draw_batch() {
    set_batch_config_params();
    m_batch->run_batch();
    m_bdata.draw_count = m_batch->m_draw_count;
    m_bdata.quad_count = m_batch->m_quad_count;
    m_batch->reset();
}

void Renderer::set_batch_config_params() {
    m_batch->set_config_param_pos(m_bdata.pos);
    m_batch->set_config_param_width(m_bdata.width);
    m_batch->set_config_param_length(m_bdata.length);
    m_batch->set_config_param_subdivide_width(m_bdata.subdivide_width);
    m_batch->set_config_param_subdivide_length(m_bdata.subdivide_length);
}

void Renderer::process_delta() {
    m_current_frame = glfwGetTime();
    m_delta = m_current_frame - m_last_frame;
    m_last_frame = m_current_frame;
    for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
        auto shader = it->second;
        shader->use();
        shader->set_float("time", m_current_frame);
    }
}


// These should be in the Shader Class as Public methods.
void Renderer::set_shader_uniform_texture(std::string tex_name, std::string uniform) {
    auto tex_int = m_texture_man->get_tex_int(tex_name.c_str());
    if (!tex_int.has_value()) {
        throw std::runtime_error("invalid tex");
    }
    for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
        auto shader = it->second;
        shader->use();
        shader->set_int(uniform, tex_int.value());
    }
}

void Renderer::set_shader_uniform_float(std::string uniform, float value) {
    for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
        auto shader = it->second;
        shader->use();
        shader->set_float(uniform, value);
    }
}

void Renderer::set_shader_uniform_int(std::string uniform, int value) {
    for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
        auto shader = it->second;
        shader->use();
        shader->set_int(uniform, value);
    }
}

void Renderer::set_shader_uniform_vec4(std::string uniform, glm::vec4 vec4) {
    for (auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
        auto shader = it->second;
        shader->use();
        shader->set_vec4(uniform, vec4);
    }
}

// writing a shader parser so uniforms can be set on the fly.
void Renderer::set_batch_uniforms() {
    set_shader_uniform_float("v_amplitude_mult", m_sdata.v_amplitude_mult);
    set_shader_uniform_float("v_amplitude", m_sdata.v_amplitude);
    set_shader_uniform_float("v_omega_mult", m_sdata.v_omega_mult);
    set_shader_uniform_float("v_omega", m_sdata.v_omega);
    set_shader_uniform_float("v_lambda_mult", m_sdata.v_lambda_mult);
    set_shader_uniform_float("v_lambda", m_sdata.v_lambda);
    set_shader_uniform_float("v_peak_width", m_sdata.v_peak_width);
    set_shader_uniform_float("fresnel_coeff", m_sdata.fresnel_coeff);
    set_shader_uniform_float("spec_coeff", m_sdata.spec_coeff);
}

void Renderer::set_phong_uniforms() {
    if (m_sdata.set_null) { set_shader_uniform_texture("NULL", "texture01"); }
    if (m_sdata.set_king) { set_shader_uniform_texture("king_canute", "texture01"); }
    if (m_sdata.set_face) { set_shader_uniform_texture("awesome_face", "texture01"); }
    if (m_sdata.set_back) { set_shader_uniform_texture("tiled_back", "texture01"); }
    if (m_sdata.set_sand) { set_shader_uniform_texture("minecraft_sand", "texture01"); }
}

void Renderer::set_toon_uniforms() {
    set_shader_uniform_int("buckets", m_sdata.toon_buckets);
}

void Renderer::set_light_uniforms() {
    set_shader_uniform_float("ambient_strength", m_sdata.ambient_strength);
    set_shader_uniform_vec4("light_color", m_sdata.light_color);
    set_shader_uniform_vec4("light_pos", m_sdata.light_pos);
}

void Renderer::updates_for_gui() {    
    m_gui->set_scene_data(m_sdata);
    m_gui->set_batch_data(m_bdata);
}

void Renderer::gui_updates() {
    updates_for_gui();
        update_gui_uniforms();
    if ( m_context->get_gui_focus() ) { 
        if (!m_gui->status_report()) {
            m_gui->wake_up();
        }
        m_gui->run();
        update_gui_uniforms();
    } else {
        if (m_gui->status_report()) {
            m_gui->sleep();
        }
    }
}

void Renderer::context_updates() {
    m_context->set_resolution(m_sdata.res.WIDTH, m_sdata.res.HEIGHT); // This is data from the Gui
}
