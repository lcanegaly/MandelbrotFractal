

add_executable(Fractal 
    main.cpp
    Fractal.cpp
    Gui.cpp
    Renderer.cpp
    Texture.cpp
    )


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Fractal glfw)
target_link_libraries(Fractal libGLEW.so)
target_link_libraries(Fractal libGLU.so)
target_link_libraries(Fractal libGL.so)