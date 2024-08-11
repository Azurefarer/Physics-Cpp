#include "gl_core/batch_renderer.h"

#include <iostream>

BatchRenderer::BatchRenderer() {
    m_data.quad_buffer = new Vertex[m_max_vertex];

    glGenVertexArrays(1, &m_data.quad_va);
    glBindVertexArray(m_data.quad_va);

    glGenBuffers(1, &m_data.quad_vb);
    glBindBuffer(GL_ARRAY_BUFFER, m_data.quad_vb);
    glBufferData(GL_ARRAY_BUFFER, m_max_vertex * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_index));
    
    uint32_t indices[m_max_index];
    uint32_t offset = 0;
    for (int i=0; i < m_max_index; i+=6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glGenBuffers(1, &m_data.quad_ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.quad_ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenTextures(1, &m_data.white_tex);
    glBindTexture(GL_TEXTURE_2D, m_data.white_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    uint32_t color = 0xffffffff;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

    m_data.texture_slots[0] = m_data.white_tex;

}

BatchRenderer::~BatchRenderer() {
    glDeleteVertexArrays(1, &m_data.quad_va);
    glDeleteBuffers(1, &m_data.quad_vb);
    glDeleteBuffers(1, &m_data.quad_ib);

    delete[] m_data.quad_buffer;
}

void BatchRenderer::run_batch() {
    BatchRenderer::begin_batch();
    for (float z = -m_params.length; z < m_params.length; z += m_params.subdivide_length) {
        for (float x = -m_params.width; x < m_params.width; x += m_params.subdivide_width) {
            glm::vec4 color = { (x + 10) / 20.0f, 0.2f, (z + 10) /20.0f, 1.0f };
            BatchRenderer::draw_quad(glm::vec3(x, m_params.y_pos, z), glm::vec2(m_params.subdivide_width, m_params.subdivide_length), color);
        }
    }
    BatchRenderer::end_batch();
    BatchRenderer::flush();
}

void BatchRenderer::begin_batch() {
    m_data.quad_buffer_ptr = m_data.quad_buffer;
}

void BatchRenderer::end_batch() {
    GLsizeiptr size = (uint8_t*)m_data.quad_buffer_ptr - (uint8_t*)m_data.quad_buffer;
    glBindBuffer(GL_ARRAY_BUFFER, m_data.quad_vb);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_max_vertex, m_data.quad_buffer);
}

void BatchRenderer::flush() {
    for (uint32_t i=0; i < m_data.tex_slot_index; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_data.texture_slots[i]);
    }
    glBindVertexArray(m_data.quad_va);
    glDrawElements(GL_TRIANGLES, m_data.index_count, GL_UNSIGNED_INT, nullptr);
    m_draw_count++;

    m_data.index_count = 0;
    m_data.tex_slot_index = 1;

}

void BatchRenderer::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    if (m_data.index_count >= m_max_index) {
        BatchRenderer::end_batch();
        BatchRenderer::flush();
        BatchRenderer::begin_batch();
    }

    float texture_index = 0.0f;

    m_data.quad_buffer_ptr->position = { position.x, position.y - cos(position.x) + sin(position.z), position.z };
    m_data.quad_buffer_ptr->color = color;
    m_data.quad_buffer_ptr->uv = { 0.0f, 0.0f };
    m_data.quad_buffer_ptr->tex_index = texture_index;
    m_data.quad_buffer_ptr++;

    m_data.quad_buffer_ptr->position = { position.x + size.x, position.y - cos(position.x+size.x) + sin(position.z), position.z };
    m_data.quad_buffer_ptr->color = color;
    m_data.quad_buffer_ptr->uv = { 1.0f, 0.0f };
    m_data.quad_buffer_ptr->tex_index = texture_index;
    m_data.quad_buffer_ptr++;
    
    m_data.quad_buffer_ptr->position = { position.x + size.x, position.y - cos(position.x+size.x) + sin(position.z+size.y), position.z + size.y };
    m_data.quad_buffer_ptr->color = color;
    m_data.quad_buffer_ptr->uv = { 1.0f, 1.0f };
    m_data.quad_buffer_ptr->tex_index = texture_index;
    m_data.quad_buffer_ptr++;

    m_data.quad_buffer_ptr->position = { position.x, position.y - cos(position.x) + sin(position.z+size.y), position.z + size.y };
    m_data.quad_buffer_ptr->color = color;
    m_data.quad_buffer_ptr->uv = { 0.0f, 1.0f };
    m_data.quad_buffer_ptr++;
    m_data.quad_buffer_ptr->tex_index = texture_index;


    m_data.index_count += 6;
    m_quad_count++;
}
