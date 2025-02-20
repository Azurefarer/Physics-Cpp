cmake_minimum_required(VERSION 3.10)

project(physics_simulation
VERSION 0.1
DESCRIPTION "Physics Simulation project with CMake"
LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MODULE_PATH )
enable_language(C)

include(FetchContent)
# GLFW library
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  SOURCE_DIR ${PROJECT_BINARY_DIR}/opencv/glfw3
  )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw3)

# -------------- IMGUI static library creation`
# TODO: write my own imgui cmake file
add_library(imgui
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_demo.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_draw.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_tables.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_widgets.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imconfig.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_internal.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imstb_rectpack.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imstb_truetype.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imstb_textedit.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_impl_opengl3.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_impl_opengl3_loader.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_impl_opengl3.h
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_impl_glfw.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/imgui/imgui_impl_glfw.h
)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/src/external_libs/imgui)
target_include_directories(imgui PUBLIC ${glfw3_SOURCE_DIR}/include)
target_link_libraries(imgui PUBLIC ${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a)

add_library(KHR 
  ${PROJECT_SOURCE_DIR}/src/external_libs/KHR/KHR.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/KHR/khrplatform.h
)
target_include_directories(KHR PUBLIC src/external_libs)

add_library(stb_image 
  ${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.cpp
  ${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.h
)
target_include_directories(stb_image PUBLIC src/external_libs)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/external_libs/glm ${PROJECT_SOURCE_DIR}/build/glm)

add_library(glad 
  ${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.c
  ${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.h
)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC src/external_libs)
target_link_libraries(glad PUBLIC KHR)

# src libs
add_library(gl_core
  ${PROJECT_SOURCE_DIR}/src/gl_core/pipeline.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/pipeline.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/rigidbody.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/rigidbody.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/batch_renderer.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/batch_renderer.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/gpu_config.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/gpu_config.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/obj_mans.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/obj_mans.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/shader.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/shader.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/shader_parser.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/shader_parser.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/shape_man.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/shape_man.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/texture_man.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_core/texture_man.h
  ${PROJECT_SOURCE_DIR}/src/gl_core/types.h
)
target_include_directories(gl_core PUBLIC
  src
  ${glfw3_SOURCE_DIR}/include
)
target_link_libraries(gl_core PUBLIC imgui)
target_link_libraries(gl_core PUBLIC glad)
target_link_libraries(gl_core PUBLIC stb_image)
target_link_libraries(gl_core PUBLIC ${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a)
target_link_libraries(gl_core PUBLIC glm::glm)


add_library(gl_aux
  ${PROJECT_SOURCE_DIR}/src/gl_aux/quad.h
  ${PROJECT_SOURCE_DIR}/src/gl_aux/quad.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_aux/cube.h
  ${PROJECT_SOURCE_DIR}/src/gl_aux/cube.cpp
  ${PROJECT_SOURCE_DIR}/src/gl_aux/vertex.h
)
target_include_directories(gl_aux PUBLIC
  src
)
target_link_libraries(gl_aux PUBLIC gl_core)

add_executable(physics_simulation ${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp)
target_include_directories(physics_simulation PUBLIC src)
target_link_libraries(physics_simulation PRIVATE glm::glm)
target_link_libraries(physics_simulation PRIVATE imgui)
target_link_libraries(physics_simulation PRIVATE stb_image)
target_link_libraries(physics_simulation PRIVATE gl_core)
target_link_libraries(physics_simulation PRIVATE gl_aux)
  