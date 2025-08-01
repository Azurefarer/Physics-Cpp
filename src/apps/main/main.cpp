#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
//#define GLFW_INCLUDE_NONE
//
//#include "GLFW/glfw3.h"

#include "core/engine.h"

int main() {
    bool success = true;
    try {
        Engine engine;
        while (engine.context_active()) {
            glClearColor(0.35f, 0.7f, 0.9f, 1.0f);
            glClearDepth(1.0);
            glDepthFunc(GL_LEQUAL); // Draw if depth is <= current val
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            engine.run();
        }
    } catch (std::exception& e) {
        success = false;
        std::cerr << "main: error - " << e.what() << std::endl;
    } catch (...) {
        success = false;
        std::cerr << "main: unknown exception" << std::endl;
    }
    return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}

// Make a framebuffer shader for advanced post processing like
// Shadow Mapping, Deferred Shading, Using colors as a compass.                                     

// Prompt GPT with this

// Turn everything into a batch render.  NVM
// Put the Shyapes and batch renderer into the same sort of implementation
// So that I can include subdivisions on assets.
// I do not need an entire batch (10,000 vertices of memory) to render a cube with 26
// The logic for generating vertices for a subdivided cube may be cumbersome.
// Easily enough I could symmetrically subdivide the cube on all axes, similar to Blender's 'Slice' tool
// However if I want to give the customizability to individually subdivide on each axis
// I think this will cause some trouble in the logic.
