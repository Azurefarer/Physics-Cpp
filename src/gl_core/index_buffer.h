#ifndef GL_CORE_INDEX_BUFFER_H_
#define GL_CORE_INDEX_BUFFER_H_

class IndexBuffer {
    private:
        unsigned int m_renderer_ID = 1;
        unsigned int m_count = 0;
    public:
        IndexBuffer(std::vector<unsigned int>* data);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int get_count() const { return m_count; }
};
#endif
