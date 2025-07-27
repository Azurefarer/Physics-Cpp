# src/gl_core/core/CMakeLists.txt

add_library(core
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/context.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/context.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/engine.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/engine.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/input.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/input.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/services.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/services.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/core/vertex.h
)
target_include_directories(core PUBLIC
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/external_libs
    ${PROJECT_SOURCE_DIR}/src/external_libs/glfw
)
target_link_libraries(core PUBLIC 
    glfw
    glad
    glm::glm
    asset
    cache
    scene
    servers
)
