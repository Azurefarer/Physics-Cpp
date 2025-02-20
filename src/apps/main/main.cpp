#include "gl_core/pipeline.h"
#include <memory>
#include <string>
#include <utility>

int main() {
    auto context = std::make_shared<Context>(1920, 1080, std::string("OpenGL Application"));
    IO io(context);
    Camera camera(context);
    Renderer renderer(context);

    while(context->is_live()) {
        glClearColor(0.35f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context->run();
        io.run();
        camera.run();
        renderer.run();
        context->swap_buffers();
    }
    return 0;
}

// Make a framebuffer shader for advanced post processing like
// Shadow Mapping, Deferred Shading, Using colors as a compass.                                     

// Prompt GPT with this

// Turn everything into a batch render.  NVM
// Put the shape man and batch renderer into the same sort of implementation
// So that I can include subdivisions on assets.
// I do not need an entire batch (10,000 vertices of memory) to render a cube with 26
// The logic for generating vertices for a subdivided cube may be cumbersome.
// Easily enough I could symmetrically subdivide the cube on all axes, similar to Blender's 'Slice' tool
// However if I want to give the customizability to individually subdivide on each axis
// I think this will cause some trouble in the logic.
