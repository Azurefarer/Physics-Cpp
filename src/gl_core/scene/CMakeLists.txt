# src/gl_core/scene/CMakeLists.txt

add_library(scene
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/camera.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/camera.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/observer.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/observer.h
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/scene.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/scene/scene.h
)
target_include_directories(scene PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/gl_core/assets
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/external_libs
)
target_link_libraries(scene PUBLIC cache)
target_link_libraries(scene PUBLIC physics)
target_link_libraries(scene PUBLIC glfw)
target_link_libraries(scene PUBLIC glad)
target_link_libraries(scene PUBLIC glm::glm)
