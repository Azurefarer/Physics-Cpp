# src/gl_core/cache/asset/CMakeLists.txt

add_library(asset
    ${PROJECT_SOURCE_DIR}/src/gl_core/asset/material.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/asset/mesh.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/asset/object.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/asset/shader.cpp
    # ${PROJECT_SOURCE_DIR}/src/gl_core/cache/asset/texture.cpp
)
target_include_directories(asset PUBLIC
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/external_libs
)
target_link_libraries(asset PUBLIC 
    glad
    glm::glm
)
