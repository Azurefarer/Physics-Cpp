#pragma once

class IndexBuffer {
    private:
        unsigned int m_renderer_ID = 0;
        unsigned int m_count = 0;
    public:
        IndexBuffer(const void* data, unsigned int count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int get_count() const { return m_count; }
};
