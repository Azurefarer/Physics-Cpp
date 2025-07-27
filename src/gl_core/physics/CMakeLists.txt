# src/gl_core/physics/CMakeLists.txt

add_library(physics
    ${PROJECT_SOURCE_DIR}/src/gl_core/physics/physic.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/physics/physic.h
)
target_include_directories(physics PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/gl_core/
    ${PROJECT_SOURCE_DIR}/src/gl_core/asset
)
target_link_libraries(physics PUBLIC asset)
target_link_libraries(physics PUBLIC glfw)
target_link_libraries(physics PUBLIC glad)
target_link_libraries(physics PUBLIC glm::glm)
