#ifndef GL_CORE_OBJ_MANS_H_
#define GL_CORE_OBJ_MANS_H_
// Rename to Systems
#include <memory>

#include "glm/gtc/matrix_transform.hpp"

#include "gl_aux/vertex.h"
#include "gl_core/shader.h"

// obj_mans are managerts of certain types of things in the program
// this is so that the gui can easily access things put into the scene
// Non Spatial Objects track data and specifically cannot be renderered unless attached to a UIObject
//      e.g. Timer, 
// Spatial Objects can be put in a specific place in the scene and can optionally have renderable things attached
//      e.g. 

class System {
    public:
        System();
        ~System() {};
};

// Renderable Systems
class OpenSystem {
    public:
        OpenSystem(MVP mvp) { m_mvp = mvp; }
        ~OpenSystem() {};
    private:
        MVP m_mvp; // Systems should really only know about their model matrix and report it to the renderer.
        std::shared_ptr<Shader> m_shader = nullptr;
};

class ClosedSystem {
    public:
        ClosedSystem(MVP mvp) { m_mvp = mvp; } // Must have an MVP associated with it to exist in space.
        ~ClosedSystem() {};
    private:
        MVP m_mvp;
        std::shared_ptr<Shader> m_shader = nullptr;
};

// Non-Renderable Systems
class AbstractSystem {
    public:
        AbstractSystem();
        ~AbstractSystem() {};

    private:

};

#endif