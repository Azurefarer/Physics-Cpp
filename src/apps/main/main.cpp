#include "gl_core/pipeline.h"

int main() {
    Context context(1500, 975, "OpenGL Application");
    Renderer renderer(context);
    renderer.run();
}
