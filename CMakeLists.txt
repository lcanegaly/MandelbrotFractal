cmake_minimum_required(VERSION 3.0.0)
project(Fractal VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.6/include)
add_subdirectory(MandelbrotFractal/Source)
add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.6)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
