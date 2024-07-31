#ifndef GL_CORE_TEXTURE_MAN_H_
#define GL_CORE_TEXTURE_MAN_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "gl_core/renderer.h"
#include "stb_image/stb_image.h"

struct Texture {
    unsigned int id;
    int width, height, nrChannels;
    unsigned int texture_units;
    Texture(unsigned int count) { id = 0; width = 0; height = 0; nrChannels = 0; texture_units = count;}
};

class TextureMan {
    public:
        TextureMan();
        TextureMan(std::string key, std::string path);
        ~TextureMan();

        void add_texture(std::string key, std::string path);
        void set_texture_params();

        void bind();
        void unbind();
        
        std::optional<unsigned int> get_texture(std::string texture);
        
    private:
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
        int m_amt_of_textures = 0;
};

#endif
