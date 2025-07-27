#ifndef GL_CORE_TEXTURE_MAN_H_
#define GL_CORE_TEXTURE_MAN_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

enum ArtStyle {
    PIXEL,
    REALISTIC
};

struct Texture {
    unsigned int id;
    int width, height, nrChannels;
    unsigned int texture_units;
    Texture(unsigned int count) { id = 0; width = 0; height = 0; nrChannels = 0; texture_units = count; }
};

class TextureMan {
    public:
        TextureMan();
        TextureMan(std::string key, std::string path);
        ~TextureMan();

        void load_stock_textures();
        void add_texture(std::string key, std::string path, std::string style);
        void set_texture_params();
        void set_pixel_texture_params();
        // TODO: add remove functionality
        
        std::optional<unsigned int> get_tex_int(std::string texture);
        std::optional<std::string> get_tex_uniform(std::string texture);
        
    private:
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
        int m_amt_of_textures = 0;
};

#endif
