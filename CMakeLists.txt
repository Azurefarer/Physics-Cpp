cmake_minimum_required(VERSION 3.10)

project(physics_simulation
VERSION 0.1
DESCRIPTION "Physics Simulation project with CMake"
LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MODULE_PATH )
enable_language(C)

include(FetchContent)
# GLFW library
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  SOURCE_DIR ${PROJECT_BINARY_DIR}/opencv
  )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw3)

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

add_library(glad 
  ${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.c
  ${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.h
)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC src/external_libs)
target_link_libraries(glad PUBLIC KHR)

# src libs
add_library(shader
  ${PROJECT_SOURCE_DIR}/src/shader_class/shader_class.cpp 
  ${PROJECT_SOURCE_DIR}/src/shader_class/shader_class.h
)
target_include_directories(shader PUBLIC
  src
  ${glfw3_SOURCE_DIR}/include
)
target_link_libraries(shader PUBLIC glad)
target_link_libraries(shader PUBLIC ${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a)

add_library(user_input
  ${PROJECT_SOURCE_DIR}/src/user_input/user_input.cpp
  ${PROJECT_SOURCE_DIR}/src/user_input/user_input.h 
)
target_include_directories(user_input PUBLIC
  src
  ${glfw3_SOURCE_DIR}/include
)
target_link_libraries(user_input PUBLIC glad)
target_link_libraries(user_input PUBLIC ${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a)

add_executable(physics_simulation 
  ${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp
  ${PROJECT_SOURCE_DIR}/src/tutorial/tutorial.cpp 
  ${PROJECT_SOURCE_DIR}/src/exercises/exercises.cpp
)
target_include_directories(physics_simulation PUBLIC src)

# Necessary libraries for project to compile at compile-time
# target_link_libraries(physics_simulation PRIVATE glad)
target_link_libraries(physics_simulation PRIVATE shader)
target_link_libraries(physics_simulation PRIVATE user_input)
target_link_libraries(physics_simulation PRIVATE stb_image)

# neccessary compile features to compile(basically like the version of the compiler)
# target_compile_features(physics_simulation PRIVATE cxx_std_17)
