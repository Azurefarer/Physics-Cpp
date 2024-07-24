#include "gl_core/gpu_config.h"

Shape::Shape(std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    va.bind();
    vb(vertex_data);
    layout.push_float(3);
    layout.push_float(3);
    layout.push_float(2);
    va.add_buffer(vb, layout);
    IndexBuffer ib(index_data);
    element_count = std::size(*index_data);
}

ShapesDict::ShapesDict() {

}

ShapesDict::~ShapesDict() {

}

void ShapesDict::shove_vertex_index_data(std::string key, std::vector<Vertex>* vertex_data, std::vector<unsigned int>* index_data) {
    m_shapes[key] = {vertex_data, index_data};   
    std::cout << "step success" << std::endl;

}

void ShapesDict::draw(std::string key) {
    m_shapes.at(key).va.bind();
    GL_call(glDrawElements(GL_TRIANGLES, m_shapes.at(key).element_count, GL_UNSIGNED_INT, (const void*)0));
    m_shapes.at(key).va.unbind();
}
