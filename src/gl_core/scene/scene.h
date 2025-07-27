#ifndef SCENE_SCENE_H_
#define SCENE_SCENE_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>
#include <vector>

#include "asset/object.h"
#include "core/services.h"
#include "core/vertex.h"
#include "scene/camera.h"
#include "scene/observer.h"

class Scene {
    // friend class Renderer;   Can do this to share view and projection data from camera
    public:
        Scene(const std::shared_ptr<Services>& pservices);
        int add_rb(const std::shared_ptr<Mesh>& mesh = nullptr, const std::shared_ptr<Material>& material = nullptr);
        const std::unordered_map<int, std::shared_ptr<Image>>& get_images() const { return m_images; }
        void run();

    private:
        int m_render_ids = 0;
        std::shared_ptr<Services> m_services;
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<Observer> m_observer;
        std::unordered_map<int, std::shared_ptr<Image>> m_images;
        // std::unordered_map<int, std::shared_ptr<Object>> m_objects;
};

#endif // SCENE_SCENE_H_
