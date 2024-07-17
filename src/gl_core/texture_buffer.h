#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <optional>
#include <vector>

#include "gl_core/renderer.h"
#include "stb_image/stb_image.h"

typedef struct {
    std::vector<unsigned int> id
}

class TextureBuffer {
    public:
        TextureBuffer();
        TextureBuffer(const char* path);
        ~TextureBuffer();

        // void set_texture(const char* path, int texture);
        void add_texture(const char* path);
        void set_texture_params();

        void bind();
        void unbind();
        
        std::optional<unsigned int> get_texture(int texture);
        
    private:
        std::vector<unsigned int> m_texture_ID;
        std::vector<int> m_width, m_height, m_nrChannels;

        std::vector<unsigned int> m_texture_units;
        int m_amt_of_textures = 0;
};
#endif
