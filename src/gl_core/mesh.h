#ifndef GL_CORE_MESH_H_
#define GL_CORE_MESH_H_

#include<iostream>

#include <map>
#include <memory>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "glad/glad.h"

#include "gl_core/vertex.h"

struct MeshData {
    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;
};

MeshData generate_sphere(float r, int rows, int columns);

extern const std::vector<Vertex> cube_vertices;
extern const std::vector<unsigned int> cube_indices;
extern const std::vector<Vertex> quad_vertices;
extern const std::vector<unsigned int> quad_indices;

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class IndexBuffer {
    public:
        IndexBuffer(const std::vector<unsigned int>& data);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int get_count() const { return m_count; }
    private:
        GLuint m_renderer_ID = 1;
        unsigned int m_count = 0;
};

class VertexBuffer {
    public:
        VertexBuffer(const std::vector<Vertex>& data);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    private:
        GLuint m_renderer_ID = 1;
};

class VertexBufferLayout {
    public:
        VertexBufferLayout();
        ~VertexBufferLayout() = default;

        void push_float(unsigned int count);
        void push_unsigned_int(unsigned int count);
        void push_unsigned_char(unsigned int count);

        const std::vector<VertexBufferElement> get_elements() const { return m_elements; }
        unsigned int get_stride() const { return m_stride; }

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride = 0;
};

class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind();
        void unbind();

    private:
        GLuint m_renderer_ID = 1;
};

// # Shader Storage Buffer Objects (SSBO)

// Shader Storage Buffer Objects allow shaders to read and write large blocks of memory. Unlike uniform buffers, SSBOs can be much larger and support random write access from compute or rendering shaders.

// ## GLSL Declaration
// ```glsl
// layout(std430, binding = 0) buffer ParticleData {
//     vec4 position[];
// };
// ```
// This buffer can be bound in your application and updated by a compute shader.

// ## Typical Usage
// 1. Create a buffer with `glGenBuffers` and `glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer)`.
// 2. Fill or map the buffer with initial data.
// 3. Dispatch a compute shader or draw call that accesses the buffer.
// 4. Optionally read back or use the results in later rendering passes.

// SSBOs are ideal for physics data such as positions, velocities, and collision results because the GPU can modify them directly.

class Ssbo {
    public:
        Ssbo() = default;
        ~Ssbo() = default;

        void add_data(const glm::vec4& data);
    private:
        GLuint m_renderer_ID = 1;
};

class Mesh {
    public:
        Mesh(std::vector<Vertex> verts, std::vector<unsigned int> indices);
        void bind() const { (*m_va_ptr.get()).bind(); }
        void unbind() const { (*m_va_ptr.get()).unbind(); }
        void draw();
        unsigned int get_element_count() const { return m_element_count; }

    private:
        std::unique_ptr<VertexArray> m_va_ptr;
        std::unique_ptr<VertexBuffer> m_vb_ptr;
        std::unique_ptr<VertexBufferLayout> m_layout_ptr;
        std::unique_ptr<IndexBuffer> m_ib_ptr;
        unsigned int m_element_count = 0;
};

class ShapeCache {
    public: 
        ShapeCache();
        ~ShapeCache() = default;
        void draw(std::string shape_name);
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_shapes;

    private:
        
};

#endif
