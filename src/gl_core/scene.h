#ifndef GL_CORE_SCENE_H_
#define GL_CORE_SCENE_H_

#include <iostream>
#include <memory>
#include <vector>

#include <gl_core/camera.h>
#include <gl_core/rigidbody.h>
#include <gl_core/services.h>
#include <gl_core/vertex.h>

class Scene {
    public:
        Scene(const std::shared_ptr<Services>& pservices);
        void add_rigidbody();
        void get_rigidbodies();
        void run();
    
    private:
        std::shared_ptr<Services> m_services;
        MVP m_transforms;
        std::unique_ptr<Camera> m_camera;
        std::vector<std::shared_ptr<RigidBody>> m_assets;
};

#endif
