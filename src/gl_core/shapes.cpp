#include "gl_core/shapes.h"

const std::vector<Vertex> cube_vertices = {
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)}, //back bottom left
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //back bottom left
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},
        //back bottom left
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)}, //front bottom left
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //front bottom left
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},
    //front bottom left
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)}, //back top left
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //back top left
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},
    //back top left
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)}, //front top left
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //front top left
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)},
    //front top left
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)}, //back bottom right
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //back bottom right
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},
    //back bottom right
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)}, //front bottom right
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)}, //front bottom right
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},
    //front bottom right
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)}, //back top right
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //back top right
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},
    //back top right
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)}, //front top right
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)}, //front top right
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)}
    //front top right
};

const std::vector<unsigned int> cube_indices = {
    // left face
    0, 3, 6,
    3, 6, 12,
    // right face
    15, 12, 21,
    12, 21, 18,
    // front face
    5, 17, 11,
    17, 11, 23,
    // back face
    14, 2, 20,
    2, 20, 8,
    // bottom face
    13, 16, 1,
    16, 1, 4,
    // top face
    19, 22, 7,
    22, 7, 10
};

const std::vector<Vertex> quad_vertices = {
    {glm::vec3(-0.5, -0.5, 0.0),  glm::vec4(0.2, 0.7, 0.5, 1.0),  glm::vec2(0.0, 0.0)},
    {glm::vec3(0.5, -0.5, 0.0),  glm::vec4(0.4, 0.9, 0.3, 1.0),  glm::vec2(1.0, 0.0)},
    {glm::vec3(-0.5, 0.5, 0.0),  glm::vec4(0.9, 0.7, 0.1, 1.0),  glm::vec2(0.0, 1.0)},
    {glm::vec3(0.5, 0.5, 0.0),  glm::vec4(0.3, 0.7, 0.1, 1.0),  glm::vec2(1.0, 1.0)}
};

const std::vector<unsigned int> quad_indices = {
    0, 1, 2,
    1, 2, 3
};

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data) {
    m_count = data.size();
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(data)[0], &(data)[0], GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_renderer_ID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& data) {
    glGenBuffers(1, &m_renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &(data)[0], GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_renderer_ID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::~VertexBufferLayout() {}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_renderer_ID);
    glBindVertexArray(m_renderer_ID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_renderer_ID);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    uintptr_t offset = 0;
    for (unsigned int i=0; i<elements.size(); i++) {
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() {
    glBindVertexArray(m_renderer_ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

// Shape::Shape(std::vector<Vertex> vertex_data, std::vector<unsigned int> index_data) {
//     m_va_ptr.reset(new VertexArray());
//     m_vb_ptr.reset(new VertexBuffer(vertex_data));
//     m_layout_ptr.reset(new VertexBufferLayout());
//     m_layout_ptr.get()->push_float(3);
//     m_layout_ptr.get()->push_float(4);
//     m_layout_ptr.get()->push_float(2);
//     m_layout_ptr.get()->push_float(3);
//     m_layout_ptr.get()->push_float(1);
//     m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
//     m_ib_ptr.reset(new IndexBuffer(index_data));
//     m_element_count = std::size(index_data);
// }
