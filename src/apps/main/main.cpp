#include "gl_core/pipeline.h"
#include <memory>
#include <string>
#include <utility>

int main() {
    auto context = std::make_unique<Context>(1500, 975, std::string("OpenGL Application"));
    Renderer renderer(std::move(context));
    renderer.run();
    return 0;
}
