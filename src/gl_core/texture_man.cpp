#include "gl_core/texture_man.h"

TextureMan::TextureMan() {
	stbi_set_flip_vertically_on_load(true);
}

TextureMan::TextureMan(std::string key, std::string path) {
	stbi_set_flip_vertically_on_load(true);
	m_textures[key] = std::make_unique<Texture>(m_amt_of_textures);
    glGenTextures(1, &m_textures[key]->id);
	glActiveTexture(GL_TEXTURE0 + m_amt_of_textures);
    glBindTexture(GL_TEXTURE_2D, m_textures[key]->id);

	TextureMan::set_texture_params();

	unsigned char* data = stbi_load(path.c_str(), &m_textures[key]->width, &m_textures[key]->height, &m_textures[key]->nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textures[key]->width, m_textures[key]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

	m_amt_of_textures = m_textures.size();
}

TextureMan::~TextureMan() {
	for (auto iter=m_textures.begin(); iter!=m_textures.end(); ++iter) {
    	glDeleteTextures(1, &(iter->second->id));
	}
}

void TextureMan::add_texture(std::string key, std::string path) {
	if (m_amt_of_textures >= 20) {
		throw std::runtime_error("OpenGL can only handle 20 textures at a time, you've inputted more than 20");
	} else {
		m_textures[key] = std::make_unique<Texture>(m_amt_of_textures);
		glGenTextures(1, &m_textures[key]->id);
		glActiveTexture(GL_TEXTURE0 + m_amt_of_textures);
		glBindTexture(GL_TEXTURE_2D, m_textures[key]->id);

		TextureMan::set_texture_params();

		unsigned char* data = stbi_load(path.c_str(), &m_textures[key]->width, &m_textures[key]->height, &m_textures[key]->nrChannels, 0);
   		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textures[key]->width, m_textures[key]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		m_amt_of_textures = m_textures.size();
	}
}

void TextureMan::set_texture_params() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureMan::bind() {
    
}

void TextureMan::unbind() {

}

std::optional<unsigned int> TextureMan::get_texture(std::string key) {
	auto iter = m_textures.find(key);
	if (iter == m_textures.end()) {
		return std::nullopt;
	}
	return m_textures[key]->texture_units;
}
