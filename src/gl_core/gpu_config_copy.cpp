class GpuConfig {
    public:
        GpuConfig();
        ~GpuConfig();

        void shove_vertex_data(std::vector<Vertex>* data);
        void shove_index_data(std::vector<unsigned int>* data);

        void draw(int index);

        void bind_vertex_array(int index) { (*m_va[index]).bind(); }
        void unbind_vertex_array(int index) { (*m_va[index]).unbind(); }

    private:
        std::vector<VertexArray*> m_va;
        unsigned int m_va_count = 0;
        VertexBuffer* m_vb;
        VertexBufferLayout* m_layout;
        IndexBuffer* m_ib;
        std::vector<int> m_element_count;
};

void GpuConfig::shove_vertex_data(std::vector<Vertex>* data) {
    VertexArray temp_va;
    m_va.push_back(new VertexArray());
    m_vb = new VertexBuffer(data);
    m_layout = new VertexBufferLayout();
    (*m_layout).push_float(3);
    (*m_layout).push_float(3);
    (*m_layout).push_float(2);
    (*m_va[m_va_count]).add_buffer((*m_vb), (*m_layout));
    m_va_count += 1;
}

void GpuConfig::shove_index_data(std::vector<unsigned int>* data) {
    m_ib = new IndexBuffer(data);
    m_element_count.push_back(size(*data));
}

void GpuConfig::draw(int index) {
    (*m_va[index]).bind();
    GL_call(glDrawElements(GL_TRIANGLES, m_element_count[index], GL_UNSIGNED_INT, (const void*)0));
    (*m_va[index]).unbind();
}

