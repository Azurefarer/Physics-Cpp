# src/gl_core/CMakeLists.txt

add_compile_definitions(SHADER_DIR="${PROJECT_SOURCE_DIR}/src/shader_source")

add_subdirectory(asset)
add_subdirectory(cache)
add_subdirectory(core)
add_subdirectory(misc)
add_subdirectory(physics)
add_subdirectory(scene)
add_subdirectory(servers)
