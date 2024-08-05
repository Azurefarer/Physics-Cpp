#include "gl_core/renderer.h"
#include <stdexcept>

double radian(double degrees) {
    return degrees * std::numbers::pi / 180;
}

void GL_clear_error() {
    while (glGetError() != GL_NO_ERROR);
}

bool GL_log_call(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Camera::Camera() : 
    m_pos(glm::vec3(0.0f, 0.0f, 3.0f)),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_right(glm::vec3(1.0f, 0.0f, 0.0f))
{}

void Camera::process_keyboard(int key, float delta_time) {
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

void Camera::process_mouse_movement(double x_offset, double y_offset, GLboolean constrain_pitch) {
    x_offset *= m_mouse_sensitivity;
    y_offset *= m_mouse_sensitivity;
    m_yaw += x_offset;
    m_pitch += y_offset;
    // if (m_pitch > std::numbers::pi / 4)
    //     m_pitch = std::numbers::pi / 4;
    // if (m_pitch < -std::numbers::pi / 4)
    //     m_pitch = -std::numbers::pi / 4;

    Camera::update_camera_vectors();
}

void Camera::process_mouse_scroll(double y_offset) {
    m_zoom -= y_offset;
}

void Camera::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(m_yaw) * cos(m_pitch);
    front.y = sin(m_pitch);
    front.z = sin(m_yaw) * cos(m_pitch);
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

RenderPipelineContext::RenderPipelineContext(int width, int height, std::string title) 
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

    RenderPipelineContext::set_callbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    RenderPipelineContext::init_imgui();

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    RenderPipelineContext::set_transforms();

    m_shader = std::make_unique<Shader>(
        "../src/shader_source/vertex_shader_practice.vs",
        "../src/shader_source/fragment_shader_01_practice.fs");
    // TODO: make constructor that just takes in the shapes so I can get rid of the 4 lines below
    m_shape_man = std::make_unique<ShapeMan>();
    Quad quad;
    Cube cube;
    m_shape_man->shove_vertex_index_data("QUAD", quad.get_verts(), quad.get_indices());
    m_shape_man->shove_vertex_index_data("CUBE", cube.get_verts(), cube.get_indices());
    m_texture_man = std::make_unique<TextureMan>();
    m_texture_man->add_texture("king_canute", "../src/king_canute.png", "texture01", "PIXEL");
    m_texture_man->add_texture("awesome_face", "../src/awesomeface.png", "texture02", "REALISTIC");
    RenderPipelineContext::set_texture("king_canute");    
    RenderPipelineContext::set_texture("awesome_face");    
}

RenderPipelineContext::~RenderPipelineContext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void RenderPipelineContext::init_imgui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(nullptr);
    std::cout << "imgui gone" << std::endl;                             
}

void RenderPipelineContext::run_imgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
            static float f = 0.0f;
            static int counter = 0;
    bool show_demo_window = true;
    bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();    
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void RenderPipelineContext::process_input(GLFWwindow* window) {
    float delta = RenderPipelineContext::get_delta();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->process_keyboard(RIGHT, delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->process_keyboard(LEFT, delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->process_keyboard(BACKWARD, delta);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->process_keyboard(FORWARD, delta);
}

float RenderPipelineContext::get_delta() {
    float current_frame = glfwGetTime();
    m_delta = current_frame - m_last_frame;
    m_last_frame = current_frame;
    return m_delta;
}

void RenderPipelineContext::set_texture(std::string tex_name) {
    auto tex_int = m_texture_man->get_tex_int(tex_name.c_str());
    auto tex_uniform = m_texture_man->get_tex_uniform(tex_name.c_str());
    if (!tex_int.has_value() || !tex_uniform.has_value()) {
        throw std::runtime_error("invalid tex");
    }
    m_shader->use();
    m_shader->set_int(tex_uniform.value(), tex_int.value());
}

void RenderPipelineContext::set_transforms() {
    glm::mat4 model(1.0f);
    glm::mat4 view(m_camera->get_view());
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(m_camera->get_zoom()), m_aspect_ratio, 0.1f, 100.0f);
    m_transforms["MODEL"] = model;
    m_transforms["VIEW"] = view;
    m_transforms["PROJECTION"] = projection;
}

void RenderPipelineContext::run() {
    while (!glfwWindowShouldClose(m_window)) {
        RenderPipelineContext::process_input(m_window);
        RenderPipelineContext::set_transforms();
        glClearColor(0.0f, RenderPipelineContext::get_cursor_pos_ratio()[0], RenderPipelineContext::get_cursor_pos_ratio()[1], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_shader->use();
        m_shader->set_mat4("model", m_transforms.at("MODEL"));
        m_shader->set_mat4("view", m_transforms.at("VIEW"));
        m_shader->set_mat4("projection", m_transforms.at("PROJECTION"));
        m_shape_man->draw("CUBE");

        RenderPipelineContext::run_imgui();

        glfwSwapBuffers(m_window);
		glfwPollEvents();
    }
}

void RenderPipelineContext::set_callbacks() {    
    static auto viewport_callback_static = [this](GLFWwindow* window, int width, int height) {
        RenderPipelineContext::viewport_size_callback(window, width, height);
    };
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        viewport_callback_static(window, width, height);
        }
    );

    static auto key_callback_static = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
        RenderPipelineContext::keyboard_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        key_callback_static(window, key, scancode, action, mods);
        }
    );

    static auto cursor_pos_callback_static = [this](GLFWwindow* window, double xposIn, double yposIn) {
        RenderPipelineContext::cursor_pos_callback(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xposIn, double yposIn) {
        cursor_pos_callback_static(window, xposIn, yposIn);
        }
    );

    static auto cursor_entered_callback_static = [this](GLFWwindow* window, int entered) {
        RenderPipelineContext::cursor_entered_callback(window, entered);
    };
    glfwSetCursorEnterCallback(m_window, [](GLFWwindow* window, int entered) {
        cursor_entered_callback_static(window, entered);
        }
    );

    static auto scroll_callback_static = [this](GLFWwindow* window, double xoffset, double yoffset) {
        RenderPipelineContext::scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        scroll_callback_static(window, xoffset, yoffset);
        }
    );
}

void RenderPipelineContext::viewport_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    m_aspect_ratio = static_cast<float>(m_width)/static_cast<float>(m_height);
    m_width = width;
    m_height = height;
}

void RenderPipelineContext::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static int k = 0;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        if (k%2 == 0) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            k++;
        } else {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            k++;
        }
    }
    std::cout << k << std::endl;
}

void RenderPipelineContext::cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn) {
    double x_offset = xposIn - m_cursor_pos_x;
    double y_offset = m_cursor_pos_y - yposIn;
    m_cursor_pos_x = xposIn;
    m_cursor_pos_y = yposIn;
    m_cursor_pos_ratio = {m_cursor_pos_x/m_width, m_cursor_pos_y/m_height};
    m_camera->process_mouse_movement(x_offset, y_offset);
}

void RenderPipelineContext::cursor_entered_callback(GLFWwindow* window, int entered) {
    glfwSetCursorPos(m_window, m_cursor_pos_x, m_cursor_pos_y);
}

void RenderPipelineContext::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    m_camera->process_mouse_scroll(yoffset);
}
