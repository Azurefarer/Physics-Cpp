#pragma once

int exercises();

void gen_gl_objs(unsigned int *VAO, unsigned int *VBO);

// How would I write this differently?
void bind_gl_objs(unsigned int *VAO, unsigned int *VBO, float (&vertices)[32]);

void vert_attrib_pointer_config();

void write_to_element_buffer(unsigned int *EBO, unsigned int (&indices)[6]);

void set_texture_params();