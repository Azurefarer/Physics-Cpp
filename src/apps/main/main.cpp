#include <iostream>

#include "gl_core/renderer.h"

int main() {
    Context context(1500, 975, "OpenGL Application");
    Renderer renderer(context);
    renderer.run();
}
