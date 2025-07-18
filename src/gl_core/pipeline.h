/*
This document contains the 4 core components of an OpenGL 3.0 render pipeline
using GLFW, Glad, and ImGui.
The Camera, Context, Gui, and Renderer.
*/


#ifndef GL_CORE_PIPELINE_H_
#define GL_CORE_PIPELINE_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <cmath>
#include <iostream>
#include <numbers>
#include <unordered_map>
#include <memory>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "gl_core/batch_renderer.h"
#include "gl_core/context.h"
#include "gl_core/camera.h"
#include "gl_core/shader.h"
#include "gl_core/rigidbody.h"
#include "gl_core/mesh.h"
#include "gl_core/texture_man.h"

double radian(double degrees);

enum CameraMovement {
    FORWARD = GLFW_KEY_W,
    LEFT = GLFW_KEY_A,
    BACKWARD = GLFW_KEY_S,
    RIGHT = GLFW_KEY_D
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
