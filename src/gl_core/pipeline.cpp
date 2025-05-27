#include "gl_core/pipeline.h"
#include <stdexcept>
#include <utility>

double radian(double degrees) {
    return degrees * std::numbers::pi / 180;
}

float frac(float x) {
    float intPart;
    return std::modf(x, &intPart); // Returns the fractional part
}

// though this is not random at all, it does a good job at hiding it
// it is not often that you'd be looking in the same direction twice
// in 3d.  Maybe this is considered random because the mapping has no
// Physical meaning/Logic.  e.g. why choose 512 instead of 256, or any
// of these hard-coded numbers for that matter.
glm::vec3 random3(glm::vec3 c) { 
	float j = 4096.0*sin(glm::dot(c,glm::vec3(17.0, 59.4, 15.0)));
	glm::vec3 r;
	r.z = frac(512.0*j);
	j *= .125;
	r.x = frac(512.0*j);
	j *= .125;
	r.y = frac(512.0*j);
	return r + r - glm::vec3(1.0);
}

Gui::Gui(GLFWwindow *context) {
    m_context = context;
    init(m_context);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    for (int i=0; i<m_sdata.rigidbodies; i++) {
        m_rigidbody_shader_param_references.push_back(false);
    }
    m_rigidbody_shader_param_references_iterator = m_rigidbody_shader_param_references.begin();
}

Gui::~Gui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::init(GLFWwindow *context) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

bool Gui::add_button_bool() {
    static int button_bool_counter = 0;
    if (m_rigidbody_shader_param_references_iterator != m_rigidbody_shader_param_references.end()) {
        bool temp = *m_rigidbody_shader_param_references_iterator;
        m_rigidbody_shader_param_references_iterator++;
        button_bool_counter++;
        return temp;
    } else {
        return false;
    }
}

void Gui::run() {
    start_frame("Scene Editor");
    show_diagnostics();
    set_resolution();
    if (m_sdata.toon) {
        set_toon();
    }
    set_texture();
    show_asset_data();
    // for (auto& [key, asset] : *m_assets) {
    //     if (ImGui::Button(asset->gui_bool ? (asset->get_name() + " | ON").c_str() : (asset->get_name() + " | OFF").c_str())) {
    //         asset->gui_bool = !asset->gui_bool; // Toggle the state
    //     }
    //     if (asset->gui_bool) {
    //         ImGui::Begin((asset->get_name() + " Shader Params").c_str(), &asset->gui_bool);
    //         set_shader_uniforms(*asset);
    //         // if (asset->get_shape() == "BATCH") {
    //         //     set_batch(asset->get_name());
    //         // }
    //         // if (asset->get_shape() == "CUBE") {
    //         //     set_light(asset->get_name());
    //         // }
    //         ImGui::End();
    //     }
    // }
    end_frame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::start_frame(const char* title) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5)); // Horizontal and vertical spacing
    ImGui::Begin(title);
}

void Gui::show_diagnostics() {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}

void Gui::set_resolution() {
    if (ImGui::RadioButton("2560 x 1440 : 2K", m_res_id == 0)) {
        m_sdata.res.WIDTH = 2560;
        m_sdata.res.HEIGHT = 1440;
        m_res_id = 0;
    }
    if (ImGui::RadioButton("1920 x 1080 : 1080p", m_res_id == 1)) {
        m_sdata.res.WIDTH = 1920;
        m_sdata.res.HEIGHT = 1080;
        m_res_id = 1;
    }
    if (ImGui::RadioButton("1366 x 768", m_res_id == 2)) {
        m_sdata.res.WIDTH = 1366;
        m_sdata.res.HEIGHT = 768;
        m_res_id = 2;
    }
    if (ImGui::RadioButton("1280 x 720 : 720p", m_res_id == 3)) {
        m_sdata.res.WIDTH = 1280;
        m_sdata.res.HEIGHT = 720;
        m_res_id = 3;
    }
}

void Gui::show_asset_data() {
    for (auto& asset : *m_assets) {
        if (ImGui::Button(asset->gui_bool ? (asset->get_name() + " | ON").c_str() : (asset->get_name() + " | OFF").c_str())) {
            asset->gui_bool = !asset->gui_bool; // Toggle the state
        }
        if (asset->gui_bool) {
            ImGui::Begin((asset->get_name() + " Shader Params").c_str(), &asset->gui_bool);
            set_shader_uniforms(*asset);
            ImGui::End();
        }
    }
}

void Gui::set_batch(std::string asset_name) {
    ImGui::Text("Draw Calls/Frame: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(m_bdata.draw_count).c_str());
    ImGui::Text("Quad Count: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(m_bdata.quad_count).c_str());
    ImGui::NewLine();
    ImGui::DragFloat3("position", &m_bdata.pos.x, 1.0f, -100.0, 100.0);
    (*m_assets)[0]->set_model_matrix(m_bdata.pos);
    ImGui::SliderFloat("width", &m_bdata.width, 0.01, 1000.0);
    ImGui::SliderFloat("length", &m_bdata.length, 0.01, 1000.0);
    ImGui::SliderFloat("width sub divisions", &m_bdata.subdivide_width, 0.01, 10.0);
    ImGui::SliderFloat("length sub divisions", &m_bdata.subdivide_length, 0.01, 10.0);
    static bool show_shader_params = add_button_bool();
    if (ImGui::Button(show_shader_params ? "ON" : "OFF")) {
        show_shader_params = !show_shader_params; // Toggle the state
    }
    if (show_shader_params) {
        ImGui::Begin((asset_name + " Shader Params").c_str());
        set_batch_shader();
        ImGui::End();
    }
}

void Gui::set_batch_shader() {
    ImGui::SliderFloat("v_amplitude_mult", &m_sdata.v_amplitude_mult, 0.0, 2.0);
    ImGui::SliderFloat("v_amplitude", &m_sdata.v_amplitude, 0.0, 6.0);
    ImGui::SliderFloat("v_omega_mult", &m_sdata.v_omega_mult, 0.0, 2.0);
    ImGui::SliderFloat("v_omega", &m_sdata.v_omega, 0.0, 2.0);
    ImGui::SliderFloat("v_lambda_mult", &m_sdata.v_lambda_mult, 0.0, 2.0);
    ImGui::SliderFloat("v_lambda", &m_sdata.v_lambda, 0.0, 1000.0);
    ImGui::SliderFloat("v_peak_width", &m_sdata.v_peak_width, 0.0, 1.0);
    ImGui::SliderFloat("fresnel_coeff", &m_sdata.fresnel_coeff, 0.0, 100.0);
    ImGui::SliderFloat("spec_coeff", &m_sdata.spec_coeff, 0.0, 10.0);
}

void Gui::set_shader_uniforms(RigidBody asset) {
    for (std::string shader_name : asset.get_shaders()) {
        std::shared_ptr<Shader>& shader = ShaderCache::get_instance().m_shader_programs[shader_name];
        auto uniforms = shader->get_uniform_names();
        for (const auto& [name, type] : uniforms) {
            std::visit([&](auto&& v) {
                using T = std::decay_t<decltype(v)>; // Get the type of the variant value
                // Handle each uniform type
                if constexpr (std::is_same_v<T, float>) {
                    ImGui::SliderFloat(name.c_str(), &v, 0.0f, 1000.0f);
                    shader->use();
                    shader->set_float(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, int>) {
                    ImGui::SliderInt(name.c_str(), &v, 0, 1000);
                    shader->use();
                    shader->set_int(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, bool>) {
                    ImGui::Checkbox(name.c_str(), &v);
                    shader->use();
                    shader->set_bool(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::vec2>) {
                    ImGui::SliderFloat2(name.c_str(), &v.x, 0.0f, 1000.0f);
                    shader->use();
                    shader->set_vec2(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::vec3>) {
                    ImGui::SliderFloat3(name.c_str(), &v.x, 0.0f, 1000.0f);
                    shader->use();
                    shader->set_vec3(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::vec4>) {
                    ImGui::SliderFloat4(name.c_str(), &v.x, 0.0f, 1000.0f);
                    shader->use();
                    shader->set_vec4(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::mat2>) {
                    ImGui::SliderFloat2(name.c_str(), &v[0][0], 0.0f, 1000.0f);
                    shader->use();
                    shader->set_mat2(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::mat3>) {
                    ImGui::SliderFloat3(name.c_str(), &v[0][0], 0.0f, 1000.0f);
                    shader->use();
                    shader->set_mat3(name, v);
                    shader->set_uniform(name, v);
                } else if constexpr (std::is_same_v<T, glm::mat4>) {
                    ImGui::SliderFloat4(name.c_str(), &v[0][0], 0.0f, 1000.0f);
                    shader->use();
                    shader->set_mat4(name, v);
                    shader->set_uniform(name, v);
                }
                else {
                    std::cerr << "Unknown uniform type: " << std::endl;
                }
            }, uniforms[name]);  // Access the variant by name
            
            
            // std::cout << "Type : " << type << std::endl;
            // std::cout << "Name : " << name << std::endl;
            // if (type == "float") {
            //     float temp = 1;
            //     // asset.uniform_value(name)
            //     ImGui::SliderFloat(name.c_str(), &temp, 0.0, 1000.0);
            //     shader->use();
            //     shader->set_float(name, temp);
            // } else if (type == "int")  {
            //     int temp = 1;
            //     ImGui::SliderInt(name.c_str(), &temp, 0, 1000);
            //     shader->use();
            //     shader->set_int(name, temp);
            // } else if (type == "bool")  {
            //     bool temp = 0;
            //     ImGui::Checkbox(name.c_str(), &temp);
            //     shader->use();
            //     shader->set_bool(name, temp);
            // } else if (type == "vec2")  {
            //     glm::vec2 temp(1.0);
            //     ImGui::SliderFloat2(name.c_str(), &temp.x, 0.0, 1000.0);
            //     shader->use();
            //     shader->set_vec2(name, temp);
            // } else if (type == "vec3")  {
            //     glm::vec3 temp(1.0);
            //     ImGui::SliderFloat3(name.c_str(), &temp.x, 0.0, 1000.0);
            //     shader->use();
            //     shader->set_vec3(name, temp);
            // } else if (type == "vec4")  {
            //     glm::vec4 temp(1.0);
            //     ImGui::SliderFloat4(name.c_str(), &temp.x, 0.0, 1000.0);
            //     shader->use();
            //     shader->set_vec4(name, temp);
            // } else {
            //     continue;
            // }
        };
    };
}

void Gui::set_texture() {
    ImGui::Text("Set Different Textures Here :D");
    if (ImGui::RadioButton("Blank", m_tex_id == 0)) {
        reset_texture_options();
        m_sdata.set_null = true;
        m_tex_id = 0;
    }
    if (ImGui::RadioButton("King Canute", m_tex_id == 1)) {
        reset_texture_options();
        m_sdata.set_king = true;
        m_tex_id = 1;
    }
    if (ImGui::RadioButton("Awesome Face", m_tex_id == 2)) {
        reset_texture_options();
        m_sdata.set_face = true;
        m_tex_id = 2;
    }
    if (ImGui::RadioButton("Tiled Background", m_tex_id == 3)) {
        reset_texture_options();
        m_sdata.set_back = true;
        m_tex_id = 3;
    }
    if (ImGui::RadioButton("Minecraft Sand", m_tex_id == 4)) {
        reset_texture_options();
        m_sdata.set_sand = true;
        m_tex_id = 4;
    }
}

void Gui::reset_texture_options() {
    m_sdata.set_back = false;
    m_sdata.set_face = false;
    m_sdata.set_king = false;
    m_sdata.set_null = false;
    m_sdata.set_sand = false;
}

void Gui::set_toon() {
    ImGui::DragInt("buckets", &m_sdata.toon_buckets, .01, 2, 25);
}

void Gui::set_light(std::string asset_name) {
    ImGui::DragFloat3("Light Box Position", &m_sdata.light_pos.x, 1.0f, -1000.0, 1000.0);
    (*m_assets)[0]->set_model_matrix(m_sdata.light_pos);
    static bool show_shader_params = add_button_bool();
    if (ImGui::Button(show_shader_params ? "ON" : "OFF")) {
        show_shader_params = !show_shader_params; // Toggle the state
    }
    if (show_shader_params) {
        ImGui::Begin((asset_name + " Shader Params").c_str());
        set_light_shader();
        ImGui::End();
    }
}

void Gui::set_light_shader() {
    ImGui::SliderFloat("Ambient Strength", &m_sdata.ambient_strength, 0.0, 1.0);
    ImGui::ColorPicker4("Light_Color", &m_sdata.light_color.x);
}

void Gui::end_frame() {
    ImGui::PopStyleVar();
    ImGui::End();
    ImGui::Render();
}

void Gui::set_rigidbodies(const std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>>& assets) {
    m_assets = assets;
}

// Sleep and Wake Up are probably not needed
void Gui::sleep() {
    m_rigidbody_shader_param_references.clear();
}

void Gui::wake_up() {
    for (int i=0; i<m_sdata.rigidbodies; i++) {
        bool temp = false;
        m_rigidbody_shader_param_references.push_back(false);
    }
    m_rigidbody_shader_param_references_iterator = m_rigidbody_shader_param_references.begin();
}

Context::Context(int width, int height, std::string title) 
    : m_width(width), m_height(height), m_cursor_pos_x(width/2), m_cursor_pos_y(height/2) {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL) { 
		glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
	}
    glfwMakeContextCurrent(m_window);
    glfwSetWindowPos(m_window, 0, 10); // Make this flush with OS taskbar or fullscreen it.
    set_GLFWcallbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
    glfwSwapInterval(0);
    glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    set_GLcallbacks();
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Context::~Context() {
    glfwTerminate();
}

void Context::run() {
    glfwPollEvents();

    m_current_frame = glfwGetTime();
    m_delta = m_current_frame - m_last_frame;
    m_last_frame = m_current_frame;
}

void Context::set_MVP(glm::mat4 view, double zoom) {
    // m_mvp.model = glm::mat4(1.0f);
    m_mvp.view = view;

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(static_cast<float>(zoom)), get_aspect_ratio(), 0.1f, 4000.0f);
    m_mvp.projection = projection;
}

void Context::set_resolution(int width, int height) {
    glfwSetWindowSize(m_window, width, height);
}

void Context::swap_buffers() {
    glfwSwapBuffers(m_window);
}

void Context::set_GLcallbacks() {
    static auto message_callback_static = [this](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        Context::message_callback(source, type, id, severity, length, message, userParam);
    };
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            message_callback_static(source, type, id, severity, length, message, userParam);},
        0
    );
}

void Context::message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) { 
    if (type == GL_DEBUG_TYPE_OTHER) {
            return;
    }
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message
    );
};

void Context::set_GLFWcallbacks() {   
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
    if ( action == GLFW_REPEAT ) {
        return;
    }
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_ESCAPE ) {
            glfwSetWindowShouldClose(window, true);
        }
        if ( key == GLFW_KEY_TAB ) {
            if ( m_gui_focus == false ) {
                (*m_keys).Ltab_key = key;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                set_gui_focus(true);
            } else {
                (*m_keys).Ltab_key = -1;
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                set_gui_focus(false); 
            }
        }
        if ( key == GLFW_KEY_W ) {
            (*m_keys).W_key = key;
        }
        if ( key == GLFW_KEY_A ) {
            (*m_keys).A_key = key;
        }
        if ( key == GLFW_KEY_S ) {
            (*m_keys).S_key = key;
        }
        if ( key == GLFW_KEY_D ) {
            (*m_keys).D_key = key;
        }
    }
    if ( action == GLFW_RELEASE ) {
        if ( key == GLFW_KEY_W ) {
            (*m_keys).W_key = -1;
        }
        if ( key == GLFW_KEY_A ) {
            (*m_keys).A_key = -1;
        }
        if ( key == GLFW_KEY_S ) {
            (*m_keys).S_key = -1;
        }
        if ( key == GLFW_KEY_D ) {
            (*m_keys).D_key = -1;
        }
    }
}

void Context::cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn) {
    m_arc_x += xposIn - m_cursor_pos_x;
    m_arc_y += m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};

    set_cursor_activity(true);
}

void Context::cursor_entered_callback(GLFWwindow* window, int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void Context::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    m_scroll_x_offset = xoffset;
    m_scroll_y_offset = yoffset;
    
    m_scroll_activity = true;
}

Camera::Camera(std::shared_ptr<Context> pcontext) : 
    m_context(pcontext),
    m_pos(glm::vec3(0.0f, 0.0f, 1000.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    m_yaw = 0;
    m_pitch = 0.0;
    update_camera_vectors();
    set_view();
    m_context->set_MVP(m_view, m_zoom);
}

void Camera::run() {
    set_control(!m_context->get_gui_focus());
    int *iter = &(m_context->get_keys_pressed()->W_key); // Memory Address Starts at the beginning of the keys struct.
    for ( int i=0; i*4<sizeof(keys); i++ ) { 
        int key = *(iter);
        process_keyboard(key, m_context->get_delta_time());
        iter++;
    }
    if ( m_context->get_cursor_activity() ) {
        process_mouse_movement(m_context->get_arc_x(), m_context->get_arc_y());
        m_context->set_cursor_activity(false);
        m_context->set_arc_x(0);
        m_context->set_arc_y(0);
    } else {}
    if ( m_context->get_scroll_activity() ) {
        process_mouse_scroll(m_context->get_scroll_y());
        m_context->set_scroll_activity(false);
    } else {}
    set_view();
    m_context->set_MVP(m_view, m_zoom);
}

void Camera::set_view() {
    glm::vec3 target = m_pos + m_front;
    m_view = glm::lookAt(m_pos, target, m_up); 
}

void Camera::set_control(bool activity) {
    m_active = activity;
}

void Camera::process_keyboard(int key, float delta_time) {
    if (m_active) {
        // std::cout << key << std::endl;
        float velocity = m_movement_speed * delta_time;
        if (key == GLFW_KEY_W) 
            m_pos += m_front * velocity; 
        if (key == GLFW_KEY_A)
            m_pos -= m_right * velocity;
        if (key == GLFW_KEY_S)
            m_pos -= m_front * velocity;
        if (key == GLFW_KEY_D)
            m_pos += m_right * velocity;
            // std::cout << glm::to_string(m_right) << std::endl;
    } else { return; }
}

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    if (m_active) { 
        x_offset /= m_mouse_sensitivity; // This acts as the radius of
        y_offset /= m_mouse_sensitivity; // the circle the camera looks within.
        m_yaw += x_offset; // negative because z-axis is flipped
        m_pitch += y_offset;
        if (m_pitch >= std::numbers::pi / 2)
            m_pitch = std::numbers::pi / 2;
        if (m_pitch <= -std::numbers::pi / 2)
            m_pitch = -std::numbers::pi / 2;
        Camera::update_camera_vectors(); 
    } else { 
        return; 
    }
}

void Camera::update_camera_vectors() {
    m_front.x = sin(m_yaw) *    cos(m_pitch);
    m_front.y =                 sin(m_pitch);
    m_front.z = -cos(m_yaw) *   cos(m_pitch);
    m_right =   glm::normalize(glm::cross(m_front, m_world_up)); // Have to normalize otherwise looking down restricts left and right movement
    m_up =      glm::cross(m_right, m_front);
}

void Camera::process_mouse_scroll(double y_offset) {
    if (!m_active) { return; }
    else {
        m_zoom -= y_offset; // Scroll down will zoom out, that is, increase the fovy
    }
}

IO::IO(std::shared_ptr<Context> pcontext) : m_context(pcontext) {}

IO::~IO() {}

void IO::run() {
    
}

Renderer::Renderer(std::shared_ptr<Context> pcontext) : m_context(pcontext) {
    m_assets = std::make_shared<std::vector<std::shared_ptr<RigidBody>>>();
    m_batch = std::make_unique<BatchRenderer>();
    m_texture_man = std::make_unique<TextureMan>();
    m_gui = std::make_unique<Gui>(m_context->get_window());
    set_MVP(glm::vec3(0.0), glm::vec3(1.0f));
    rigidbody_push_back(m_transforms);
    rigidbody_push_back(m_transforms);
    rigidbody_push_back(m_transforms);
    set_shader_uniform_texture("NULL", "texture01");
    update_gui_uniforms();
    (*m_assets)[0]->set_model_matrix(m_sdata.light_pos);
}

void Scene::add_rigidbody(const MVP& mvp) {
    m_assets.push_back(std::make_shared<RigidBody>(mvp));
}

void Renderer::run() {
    process_delta();
    draw();

    gui_updates();
    context_updates();
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
    // Re-Write Key Structure
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
    // set_light_uniforms();
    // set_phong_uniforms();
    // set_batch_uniforms();
    // set_toon_uniforms();
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

// Gotta have a shader uniform manager

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

// void Renderer::add_object() {}

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

void Diagnostics_print() {
    
}
