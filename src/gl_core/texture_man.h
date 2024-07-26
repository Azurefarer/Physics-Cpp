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
    Texture() { id = 0; width = 0; height = 0; nrChannels = 0; texture_units = 0;}
};

class TextureMan {
    public:
        TextureMan();
        TextureMan(std::string key, std::string path);
        ~TextureMan();

        // void set_texture(const char* path, int texture);
        void add_texture(std::string key, std::string path);
        void set_texture_params();

        void bind();
        void unbind();
        
        std::optional<unsigned int> get_texture(std::string texture);
        
    private:
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
        std::vector<unsigned int> m_texture_ID;
        std::vector<int> m_width, m_height, m_nrChannels;

        std::vector<unsigned int> m_texture_units;
        int m_amt_of_textures = 0;
};

#endif
