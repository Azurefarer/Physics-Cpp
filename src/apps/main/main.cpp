#include <iostream>

#include "gl_core/renderer.h"

int main() {
    RenderPipelineContext context(1500, 975, "OpenGL Application");
    context.run();
}
