#include "asset/mesh.h"

MeshData generate_sphere(float r, int rows, int columns) {
    MeshData temp;
    for (int i=0; i<=rows; ++i) {
        for (int j=0; j<=columns; ++j) {
            float theta = i / static_cast<float>(rows) * 3.141; //glm::pi<float>();
            float phi = j / static_cast<float>(columns) * 2 * 3.141; //glm::two_pi<float>();

            Vertex vert;
            vert.position[0] = r * sin(theta) * cos(phi);
            vert.position[1] = r * sin(theta) * sin(phi);
            vert.position[2] = r * cos(theta);
            temp.verts.push_back(vert);

            if (i < rows && j < columns) { // don't want to generate extra indicies
                int i0 = i * (columns + 1) + j;
                int i1 = i0 + 1;
                int i2 = i0 + (columns + 1);
                int i3 = i2 + 1;
                temp.indices.push_back(i0);
                temp.indices.push_back(i2);
                temp.indices.push_back(i1);

                temp.indices.push_back(i1);
                temp.indices.push_back(i2);
                temp.indices.push_back(i3);
            }
        }
    }
    return temp;
}

const std::vector<Vertex> cube_vertices = {
    //front bottom left
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)},    // Normal -x
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)},    // Normal -y
    {glm::vec3(-0.5, -0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},    // Normal -z
    //back bottom left
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(-1.0, 0.0, 0.0)},     // Normal -x
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)},     // Normal -y
    {glm::vec3(-0.5, -0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},      // Normal +z
    //front top left
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)},     // Normal -x
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)},      // Normal +y
    {glm::vec3(-0.5, 0.5, -0.5),  glm::vec4(0.0, 0.0, 1.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},     // Normal -z
    //back top left
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(-1.0, 0.0, 0.0)},      // Normal -x
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)},       // Normal +y
    {glm::vec3(-0.5, 0.5, 0.5),  glm::vec4(1.0, 1.0, 1.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)},       // Normal +z
    //front bottom right
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)},      // Normal +x
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)},     // Normal -y
    {glm::vec3(0.5, -0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 0.0),  glm::vec3(0.0, 0.0, -1.0)},     // Normal -z
    //back bottom right
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(1.0, 0.0, 0.0)},       // Normal +x
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)},      // Normal -y
    {glm::vec3(0.5, -0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)},       // Normal +z
    //front top right
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)},       // Normal +x
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)},       // Normal +y
    {glm::vec3(0.5, 0.5, -0.5),  glm::vec4(1.0, 0.0, 0.0, 1.0),  glm::vec2(0.0, 1.0),  glm::vec3(0.0, 0.0, -1.0)},      // Normal -z
    //back top right
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(1.0, 0.0, 0.0)},        // Normal +x
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 1.0, 0.0)},        // Normal +y
    {glm::vec3(0.5, 0.5, 0.5),  glm::vec4(0.0, 1.0, 0.0, 1.0),  glm::vec2(1.0, 1.0),  glm::vec3(0.0, 0.0, 1.0)}         // Normal +z
};

const std::vector<unsigned int> cube_indices = {
    // -x face
    0, 3, 6,
    3, 6, 9,
    // -y face
    1, 4, 13,
    4, 13, 16,
    // -z face
    2, 8, 14,
    8, 14, 20,
    // +z face
    5, 11, 17,
    11, 17, 23,
    // +y face
    7, 10, 19,
    10, 19, 22,
    // +x face
    12, 15, 18,
    15, 18, 21
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

VertexBufferLayout::VertexBufferLayout() {
    push_float(3); // vec3 pos
    push_float(4); // vec4 color
    push_float(2); // vec2 uv
    push_float(3); // vec3 normal
    push_float(1); // float tex_index
}

void VertexBufferLayout::push_float(unsigned int count) {
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
}

void VertexBufferLayout::push_unsigned_int(unsigned int count) {
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
}

void VertexBufferLayout::push_unsigned_char(unsigned int count) {
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
}

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
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(),  reinterpret_cast<void*>(offset));
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

Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> indices) {
    m_va_ptr = std::make_unique<VertexArray>();
    m_vb_ptr = std::make_unique<VertexBuffer>(verts);
    m_layout_ptr = std::make_unique<VertexBufferLayout>();
    m_va_ptr.get()->add_buffer((*m_vb_ptr.get()), (*m_layout_ptr.get()));
    m_ib_ptr = std::make_unique<IndexBuffer>(indices);
    m_element_count = m_ib_ptr->get_count();
}

// void Mesh::update_verts

void Mesh::draw() {
    bind();
    glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_INT, (const void*)0);
    unbind();
}
