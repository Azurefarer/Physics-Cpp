# Details

Date : 2025-07-18 15:46:22

Directory c:\\Users\\benji\\WorkSpace\\Cpp\\physics_simulation\\src\\gl_core

Total : 45 files,  2397 codes, 211 comments, 513 blanks, all 3121 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [src/gl\_core/CMakeLists.txt](/src/gl_core/CMakeLists.txt) | CMake | 45 | 0 | 3 | 48 |
| [src/gl\_core/assets/CMakeLists.txt](/src/gl_core/assets/CMakeLists.txt) | CMake | 15 | 0 | 3 | 18 |
| [src/gl\_core/assets/cache/CMakeLists.txt](/src/gl_core/assets/cache/CMakeLists.txt) | CMake | 14 | 0 | 2 | 16 |
| [src/gl\_core/assets/cache/cache.h](/src/gl_core/assets/cache/cache.h) | C++ | 12 | 0 | 4 | 16 |
| [src/gl\_core/assets/cache/material\_cache.cpp](/src/gl_core/assets/cache/material_cache.cpp) | C++ | 10 | 0 | 3 | 13 |
| [src/gl\_core/assets/cache/material\_cache.h](/src/gl_core/assets/cache/material_cache.h) | C++ | 14 | 0 | 5 | 19 |
| [src/gl\_core/assets/cache/mesh\_cache.cpp](/src/gl_core/assets/cache/mesh_cache.cpp) | C++ | 10 | 0 | 3 | 13 |
| [src/gl\_core/assets/cache/mesh\_cache.h](/src/gl_core/assets/cache/mesh_cache.h) | C++ | 14 | 0 | 5 | 19 |
| [src/gl\_core/assets/cache/shader\_cache.cpp](/src/gl_core/assets/cache/shader_cache.cpp) | C++ | 38 | 0 | 8 | 46 |
| [src/gl\_core/assets/cache/shader\_cache.h](/src/gl_core/assets/cache/shader_cache.h) | C++ | 16 | 0 | 4 | 20 |
| [src/gl\_core/assets/material.cpp](/src/gl_core/assets/material.cpp) | C++ | 0 | 0 | 1 | 1 |
| [src/gl\_core/assets/material.h](/src/gl_core/assets/material.h) | C++ | 19 | 1 | 9 | 29 |
| [src/gl\_core/assets/mesh.cpp](/src/gl_core/assets/mesh.cpp) | C++ | 171 | 15 | 31 | 217 |
| [src/gl\_core/assets/mesh.h](/src/gl_core/assets/mesh.h) | C++ | 107 | 15 | 35 | 157 |
| [src/gl\_core/assets/shader.cpp](/src/gl_core/assets/shader.cpp) | C++ | 225 | 5 | 24 | 254 |
| [src/gl\_core/assets/shader.h](/src/gl_core/assets/shader.h) | C++ | 62 | 6 | 9 | 77 |
| [src/gl\_core/batch\_renderer.cpp](/src/gl_core/batch_renderer.cpp) | C++ | 118 | 1 | 32 | 151 |
| [src/gl\_core/batch\_renderer.h](/src/gl_core/batch_renderer.h) | C++ | 52 | 0 | 23 | 75 |
| [src/gl\_core/camera.cpp](/src/gl_core/camera.cpp) | C++ | 84 | 0 | 9 | 93 |
| [src/gl\_core/camera.h](/src/gl_core/camera.h) | C++ | 41 | 0 | 15 | 56 |
| [src/gl\_core/core/CMakeLists.txt](/src/gl_core/core/CMakeLists.txt) | CMake | 13 | 0 | 2 | 15 |
| [src/gl\_core/core/context.cpp](/src/gl_core/core/context.cpp) | C++ | 167 | 37 | 30 | 234 |
| [src/gl\_core/core/context.h](/src/gl_core/core/context.h) | C++ | 90 | 2 | 14 | 106 |
| [src/gl\_core/core/engine.cpp](/src/gl_core/core/engine.cpp) | C++ | 13 | 0 | 3 | 16 |
| [src/gl\_core/core/engine.h](/src/gl_core/core/engine.h) | C++ | 23 | 3 | 11 | 37 |
| [src/gl\_core/core/services.cpp](/src/gl_core/core/services.cpp) | C++ | 5 | 0 | 1 | 6 |
| [src/gl\_core/core/services.h](/src/gl_core/core/services.h) | C++ | 24 | 0 | 8 | 32 |
| [src/gl\_core/core/vertex.h](/src/gl_core/core/vertex.h) | C++ | 23 | 4 | 6 | 33 |
| [src/gl\_core/gui.cpp](/src/gl_core/gui.cpp) | C++ | 258 | 55 | 25 | 338 |
| [src/gl\_core/gui.h](/src/gl_core/gui.h) | C++ | 55 | 2 | 15 | 72 |
| [src/gl\_core/physics\_object.cpp](/src/gl_core/physics_object.cpp) | C++ | 1 | 0 | 0 | 1 |
| [src/gl\_core/physics\_object.h](/src/gl_core/physics_object.h) | C++ | 17 | 0 | 8 | 25 |
| [src/gl\_core/pipeline.cpp](/src/gl_core/pipeline.cpp) | C++ | 22 | 5 | 7 | 34 |
| [src/gl\_core/pipeline.h](/src/gl_core/pipeline.h) | C++ | 69 | 11 | 22 | 102 |
| [src/gl\_core/rigidbody.cpp](/src/gl_core/rigidbody.cpp) | C++ | 30 | 2 | 8 | 40 |
| [src/gl\_core/rigidbody.h](/src/gl_core/rigidbody.h) | C++ | 41 | 0 | 10 | 51 |
| [src/gl\_core/scene.cpp](/src/gl_core/scene.cpp) | C++ | 13 | 0 | 6 | 19 |
| [src/gl\_core/scene.h](/src/gl_core/scene.h) | C++ | 22 | 0 | 6 | 28 |
| [src/gl\_core/servers/CMakeLists.txt](/src/gl_core/servers/CMakeLists.txt) | CMake | 8 | 0 | 2 | 10 |
| [src/gl\_core/servers/renderer.cpp](/src/gl_core/servers/renderer.cpp) | C++ | 158 | 2 | 26 | 186 |
| [src/gl\_core/servers/renderer.h](/src/gl_core/servers/renderer.h) | C++ | 64 | 1 | 17 | 82 |
| [src/gl\_core/tensor.cpp](/src/gl_core/tensor.cpp) | C++ | 9 | 4 | 4 | 17 |
| [src/gl\_core/tensor.h](/src/gl_core/tensor.h) | C++ | 99 | 39 | 28 | 166 |
| [src/gl\_core/texture\_man.cpp](/src/gl_core/texture_man.cpp) | C++ | 71 | 0 | 16 | 87 |
| [src/gl\_core/texture\_man.h](/src/gl_core/texture_man.h) | C++ | 35 | 1 | 10 | 46 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)