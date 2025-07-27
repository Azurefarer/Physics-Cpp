# src/gl_core/assets/CMakeLists.txt

add_library(servers
    ${PROJECT_SOURCE_DIR}/src/gl_core/servers/renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_core/servers/renderer.h
)
target_include_directories(servers PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/gl_core
    ${PROJECT_SOURCE_DIR}/src/external_libs
)
target_link_libraries(servers PUBLIC glad)
target_link_libraries(servers PUBLIC glfw)
target_link_libraries(servers PUBLIC glm::glm)
target_link_libraries(servers PUBLIC asset)
target_link_libraries(servers PUBLIC cache)
target_link_libraries(servers PUBLIC )
