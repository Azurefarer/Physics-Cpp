#ifndef GL_CORE_SCENE_H_
#define GL_CORE_SCENE_H_

#include <iostream>
#include <memory>
#include <vector>

#include <gl_core/camera.h>
#include <gl_core/rigidbody.h>
#include <gl_core/vertex.h>

class Scene {
    public:
        Scene();
        void add_rigidbody();
    
    private:
        MVP m_transforms;
        std::vector<std::shared_ptr<RigidBody>> m_assets;
};

#endif
