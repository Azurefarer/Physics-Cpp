#include "gl_core/texture_man.h"

TextureMan::TextureMan() {
	stbi_set_flip_vertically_on_load(true);
}

TextureMan::TextureMan(std::string key, std::string path) {
	stbi_set_flip_vertically_on_load(true);
	m_textures[key] = std::make_unique<Texture>();
    GL_call(glGenTextures(1, &m_textures[key]->id));
	GL_call(glActiveTexture(GL_TEXTURE0 + m_amt_of_textures));
    GL_call(glBindTexture(GL_TEXTURE_2D, m_textures[key]->id));

	TextureMan::set_texture_params();

	unsigned char* data = stbi_load(path.c_str(), &m_textures[key]->width, &m_textures[key]->height, &m_textures[key]->nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textures[key]->width, m_textures[key]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

	m_texture_units[0] = 0;
	m_amt_of_textures = m_textures.size();
}

TextureMan::~TextureMan() {
	for (int i=0; i<size(m_texture_ID); i++) {
    	GL_call(glDeleteTextures(1, &m_texture_ID[i]));
	}
}

void TextureMan::add_texture(std::string key, std::string path) {
	if (m_amt_of_textures >= 20) {
		throw std::runtime_error("OpenGL can only handle 20 textures at a time, you've inputted more than 20");
	} else {
		m_texture_ID.push_back(m_amt_of_textures);
		m_width.push_back(m_amt_of_textures);  m_height.push_back(m_amt_of_textures);  m_nrChannels.push_back(m_amt_of_textures);
		GL_call(glGenTextures(1, &m_texture_ID[m_amt_of_textures]));
		GL_call(glActiveTexture(GL_TEXTURE0 + m_amt_of_textures));
	    GL_call(glBindTexture(GL_TEXTURE_2D, m_texture_ID[m_amt_of_textures]));
		TextureMan::set_texture_params();

		unsigned char* data = stbi_load(path.c_str(), &m_width[m_amt_of_textures], &m_height[m_amt_of_textures], &m_nrChannels[m_amt_of_textures], 0);
		GL_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width[m_amt_of_textures], m_height[m_amt_of_textures], 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		m_texture_units.push_back(m_amt_of_textures);
		m_amt_of_textures = size(m_texture_units);
	}
}

void TextureMan::set_texture_params() {
	GL_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void TextureMan::bind() {
    
}

void TextureMan::unbind() {

}

std::optional<unsigned int> TextureMan::get_texture(std::string texture) {
	auto iter = m_textures.find(texture);
	if (iter != m_textures.end()) {
		return std::nullopt;
	}
	return (*m_textures[texture]).id;
}
