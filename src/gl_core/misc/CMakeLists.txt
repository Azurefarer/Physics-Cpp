# src/gl_core/misc/CMakeLists.txt

add_library(misc
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/batch_renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/batch_renderer.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/physics_object.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/physics_object.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/tensor.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/misc/tensor.h
)
target_include_directories(misc PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/gl_core/assets
)
target_link_libraries(misc PUBLIC glfw)
target_link_libraries(misc PUBLIC glad)
target_link_libraries(misc PUBLIC glm::glm)
