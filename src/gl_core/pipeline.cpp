#include "gl_core/pipeline.h"
#include <stdexcept>

double radian(double degrees) {
    return degrees * std::numbers::pi / 180;
}

Camera::Camera() : 
    m_pos(glm::vec3(0.0f, 3.0f, 10.0f)),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_right(glm::vec3(1.0f, 0.0f, 0.0f))
{}

void Camera::set_control(bool activity) {
    m_active = activity;
}

void Camera::process_keyboard(int key, float delta_time) {
    if (!m_active) { return; }
    else {
        float velocity = m_movement_speed * delta_time;
        if (key == GLFW_KEY_W)
            m_pos += m_front * velocity;
        if (key == GLFW_KEY_S)
            m_pos -= m_front * velocity;
        if (key == GLFW_KEY_A)
            m_pos -= m_right * velocity;
        if (key == GLFW_KEY_D)
            m_pos += m_right * velocity;
    }
}

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    // Can change this so the math makes more sense
    // instead of adding linear offset to an angular total value
    // convert the liinear offset into an angle measurement with arc length.
    
    if (!m_active) { return; }
    else {
        x_offset /= m_mouse_sensitivity; // This acts as the radius of
        y_offset /= m_mouse_sensitivity; // the circle the camera looks within.
        m_yaw += x_offset;
        m_pitch += y_offset;
        if (m_pitch > std::numbers::pi / 2)
            m_pitch = std::numbers::pi / 2;
        if (m_pitch < -std::numbers::pi / 2)
            m_pitch = -std::numbers::pi / 2;

        Camera::update_camera_vectors();
    }
}

void Camera::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(m_yaw) * cos(m_pitch);
    front.y = sin(m_pitch);
    std::cout << front.y << "HI" << std::endl;
    std::cout << m_pitch << "HI" << std::endl;
    front.z = sin(m_yaw) * cos(m_pitch);
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::process_mouse_scroll(double y_offset) {
    if (!m_active) { return; }
    else {
        m_zoom -= y_offset;
    }
}

Gui::Gui(GLFWwindow *context) { 
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init("#version 430 core");
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

Gui::~Gui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::run() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Scene Editor");
    Gui::update_frame();
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// void Gui::start_frame() {
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();
// }

void Gui::update_frame() {
    // ImGui::Begin("Hello, world!");
    ImGui::Text("Draw Calls/Frame: ", std::to_string(m_bdata.draw_count).c_str());
    // ImGui::SameLine();
    // ImGui::Text(std::to_string(m_bdata.draw_count).c_str());
    ImGui::Text("Quad Count: ", std::to_string(m_bdata.quad_count).c_str());
    // ImGui::SameLine();
    // ImGui::Text(std::to_string(m_bdata.quad_count).c_str());

    ImGui::SliderFloat("y pos of floor", &m_bdata.y_pos, -10.0, 10.0);
    ImGui::SliderFloat("width", &m_bdata.width, 0.01, 100.0);
    ImGui::SliderFloat("length", &m_bdata.length, 0.01, 100.0);
    ImGui::SliderFloat("width sub divisions", &m_bdata.subdivide_width, 0.01, 1.0);
    ImGui::SliderFloat("length sub divisions", &m_bdata.subdivide_length, 0.01, 1.0);

    ImGui::Text("Set Different Textures Here :D");
    ImGui::Checkbox("Blank", &m_sdata.set_null);
    ImGui::Checkbox("King Canute", &m_sdata.set_king);
    ImGui::Checkbox("Awesome Face", &m_sdata.set_face);
}

Context::Context(int width, int height, std::string title) 
    : m_width(width), m_height(height), m_cursor_pos_x(width/2), m_cursor_pos_y(height/2) {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL) {
		glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);

    Context::set_callbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    gui = std::make_shared<Gui>(m_window);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

Context::~Context() {
    glfwTerminate();
}

void Context::swap_buffers() {
    glfwSwapBuffers(m_window);
}

void Context::set_callbacks() {   
    static auto viewport_callback_static = [this](GLFWwindow* window, int width, int height) {
        Context::viewport_size_callback(window, width, height);
    };
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        viewport_callback_static(window, width, height);
        }
    );

    static auto key_callback_static = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Context::keyboard_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        key_callback_static(window, key, scancode, action, mods);
        }
    );

    static auto cursor_pos_callback_static = [this](GLFWwindow* window, double xposIn, double yposIn) {
        Context::cursor_pos_callback(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xposIn, double yposIn) {
        cursor_pos_callback_static(window, xposIn, yposIn);
        }
    );

    static auto cursor_entered_callback_static = [this](GLFWwindow* window, int entered) {
        Context::cursor_entered_callback(window, entered);
    };
    glfwSetCursorEnterCallback(m_window, [](GLFWwindow* window, int entered) {
        cursor_entered_callback_static(window, entered);
        }
    );

    static auto scroll_callback_static = [this](GLFWwindow* window, double xoffset, double yoffset) {
        Context::scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        scroll_callback_static(window, xoffset, yoffset);
        }
    );
}

void Context::viewport_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);
    m_width = width;
    m_height = height;
}

void Context::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static int k = 0;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        if (k%2 == 0) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_mouse_control = false;
            k++;
        } else {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_mouse_control = true;
            k++;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        (*m_keys).W_key = GLFW_KEY_W; else { (*m_keys).W_key = -1; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        (*m_keys).A_key = GLFW_KEY_A; else { (*m_keys).A_key = -1; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        (*m_keys).S_key = GLFW_KEY_S; else { (*m_keys).S_key = -1; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        (*m_keys).D_key = GLFW_KEY_D; else { (*m_keys).D_key = -1; }
}

void Context::cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn) {
    m_arc_x = xposIn - m_cursor_pos_x;
    m_arc_y = m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};
}

void Context::cursor_entered_callback(GLFWwindow* window, int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void Context::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    m_scroll_x_offset = xoffset;
    m_scroll_y_offset = yoffset;
}

Renderer::Renderer(Context context) {
    m_context = std::make_unique<Context>(context);
    m_batch = std::make_unique<BatchRenderer>();
    m_shader = std::make_unique<Shader>(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_practice.fs");
    m_shader2 = std::make_unique<Shader>(
        "../src/shader_source/vertex_lighting_shader.vs",
        "../src/shader_source/fragment_lighting_shader.fs");
    m_shape_man = std::make_unique<ShapeMan>();
    m_texture_man = std::make_unique<TextureMan>();
    m_gui = m_context->gui;
    Renderer::set_transforms(glm::vec3(0.0f));
    Renderer::set_shader_texture("NULL", "texture01");
}

Renderer::~Renderer() {}

void Renderer::run() {
    while(m_context->is_live()) {
        glfwPollEvents();
        Renderer::update_for_gui();
        m_gui->run();
        Renderer::update_from_gui();
        // m_gui->start_frame();
        glClearColor(0.35f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer::set_transforms(glm::vec3(0.0f));
        m_shader->use();
        m_batch->run_batch();
        Renderer::set_shader_uniforms();

        m_shape_man->draw("CUBE");
        Renderer::set_transforms(glm::vec3(10.0f, 7.0f, -3.0f));
        Renderer::set_shader2_uniforms();
        m_shader2->use();
        m_shape_man->draw("CUBE");
        Renderer::context_updates();
    }
}

void Renderer::set_transforms(glm::vec3 model_offset) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, model_offset);
    glm::mat4 view(m_camera->get_view());
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(m_camera->get_zoom()), m_context->get_aspect_ratio(), 0.1f, 500.0f);
    m_transforms["MODEL"] = model;
    m_transforms["VIEW"] = view;
    m_transforms["PROJECTION"] = projection;
}

void Renderer::set_shader_uniforms() {
    m_shader->use();
    m_shader->set_mat4("model", m_transforms.at("MODEL"));
    m_shader->set_mat4("view", m_transforms.at("VIEW"));
    m_shader->set_mat4("projection", m_transforms.at("PROJECTION"));
}

void Renderer::set_shader2_uniforms() {
    m_shader2->use();
    m_shader2->set_mat4("model", m_transforms.at("MODEL"));
    m_shader2->set_mat4("view", m_transforms.at("VIEW"));
    m_shader2->set_mat4("projection", m_transforms.at("PROJECTION"));
}

float Renderer::get_delta() {
    float current_frame = glfwGetTime();
    m_delta = current_frame - m_last_frame;
    m_last_frame = current_frame;

    m_shader->set_float("time", current_frame);

    return m_delta;
}

void Renderer::set_shader_texture(std::string tex_name, std::string uniform) {
    auto tex_int = m_texture_man->get_tex_int(tex_name.c_str());
    if (!tex_int.has_value()) {
        throw std::runtime_error("invalid tex");
    }
    m_shader->use();
    m_shader->set_int(uniform, tex_int.value());
}

void Renderer::update_for_gui() {
    m_bdata.draw_count = m_batch->m_draw_count;
    m_bdata.quad_count = m_batch->m_quad_count;
    
    m_gui->set_scene_data(m_sdata);
    m_gui->set_batch_data(m_bdata);
}

void Renderer::update_from_gui() {
    m_sdata = m_gui->get_scene_data();

    if (m_sdata.set_null) { Renderer::set_shader_texture("NULL", "texture01"); }
    if (m_sdata.set_king) { Renderer::set_shader_texture("king_canute", "texture01"); }
    if (m_sdata.set_face) { Renderer::set_shader_texture("awesome_face", "texture01"); }

    m_bdata = m_gui->get_batch_data();

    m_batch->set_config_param_ypos(m_bdata.y_pos);
    m_batch->set_config_param_width(m_bdata.width);
    m_batch->set_config_param_length(m_bdata.length);
    m_batch->set_config_param_subdivide_width(m_bdata.subdivide_width);
    m_batch->set_config_param_subdivide_length(m_bdata.subdivide_length);
}

void Renderer::context_updates() {
    m_camera->set_control(m_context->mouse_control());
    // Need an iterator
    int *iter = &(m_context->get_keys_pressed()->W_key); // Memory Address Starts at the beginning of the keys struct.
    for ( int i=0; i*4<sizeof(keys); i++) { 
        int key = *(iter);
        m_camera->process_keyboard(key, m_delta); 
        iter++;
    }
    m_camera->process_mouse_movement(m_context->get_arc_x(), m_context->get_arc_y());
    m_camera->process_mouse_scroll(m_context->get_scroll_y());
    m_context->swap_buffers();
}
