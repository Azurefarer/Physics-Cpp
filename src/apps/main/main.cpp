#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_core/gl_core.h"

int main() {
    RenderPipelineContext context(1500, 975, "OpenGL Application");
    context.run();
}
