#include "gl_core/pipeline.h"
#include <memory>
#include <string>
#include <utility>

int main() {
    auto context = std::make_unique<Context>(1920, 1080, std::string("OpenGL Application"));
    Renderer renderer(std::move(context));
    renderer.run();
    return 0;
}

// Make a framebuffer shader for advanced post processing like
// Shadow Mapping, Deferred Shading, Using colors as a compass. 

// Prompt GPT with this
