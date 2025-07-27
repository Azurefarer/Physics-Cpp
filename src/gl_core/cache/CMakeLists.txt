# src/gl_core/assets/CMakeLists.txt

add_library(cache
    ${PROJECT_SOURCE_DIR}/src/gl_core/cache/material_cache.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/cache/mesh_cache.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/cache/shader_cache.cpp
)
target_include_directories(cache PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/external_libs
)
target_link_libraries(cache PUBLIC asset)
