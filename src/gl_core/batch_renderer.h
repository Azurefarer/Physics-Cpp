#ifndef GL_CORE_BATCH_RENDERER_H_
#define GL_CORE_BATCH_RENDERER_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <array>

#include "glm/gtx/string_cast.hpp"

#include "gl_aux/vertex.h"
#include "glad/glad.h"

class BatchRenderer {
    public:
        BatchRenderer();
        ~BatchRenderer();

        void run_batch();

        void begin_batch();
        void end_batch();

        void flush();

        void reset();

        void draw_quad(const glm::vec3& position, const float& xsize, const float& zsize, const glm::vec4& color);

        void set_config_param_pos(glm::vec3 pos) { m_params.pos = pos; }
        void set_config_param_width(float width) { m_params.width = width; }
        void set_config_param_length(float length) { m_params.length = length; }
        void set_config_param_subdivide_width(float subdivide) { m_params.subdivide_width = subdivide; }
        void set_config_param_subdivide_length(float subdivide) { m_params.subdivide_length = subdivide; }
        
        int m_quad_count = 0; // # of Quads per render
        int m_draw_count = 0; // # of Batches per render

    private:

        static const int m_max_quad = 25000;
        static const int m_max_vertex = m_max_quad * 4;
        static const int m_max_index = m_max_quad * 6;
        static const int m_max_texs = 20;

        struct data {
            GLuint quad_va = 0;
            GLuint quad_vb = 0;
            GLuint quad_ib = 0;

            GLuint white_tex = 0;
            uint32_t white_tex_slot = 0;

            uint32_t index_count = 0;

            Vertex* quad_buffer = nullptr;
            Vertex* quad_buffer_ptr = nullptr;

            std::array<uint32_t, m_max_texs> texture_slots;
            uint32_t tex_slot_index = 1;
        };

        struct config_params {
            glm::vec3 pos = glm::vec3(0.0);
            float width = 10.0;
            float length = 10.0;
            float subdivide_width = 0.2;
            float subdivide_length = 0.2;
        };

        config_params m_params;
        data m_data;
};

#endif
