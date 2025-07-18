#ifndef GL_CORE_SERVICES_H_
#define GL_CORE_SERVICES_H_

#include "gl_core/mesh.h"
#include "gl_core/shader.h"


class Services {
    public:
        Services();
        ~Services() = default;
        std::shared_ptr<ShaderCache> m_shader_cache;
        std::shared_ptr<ShapeCache> m_shape_cache;

        const GLFWwindow* get_window() const { return m_window; }
        void set_window(GLFWwindow* window) { m_window = window; }

        const double &get_aspect_ratio() const { return m_aspect_ratio; }
        void set_aspect_ratio(double aspect_ratio) { m_aspect_ratio = aspect_ratio; }

        const MVP &get_mvp() const { return m_mvp; }
        void set_mvp(MVP mvp) { m_mvp = mvp; }
    private:
        MVP m_mvp;
        GLFWwindow* m_window;
        double m_aspect_ratio;
};

#endif
