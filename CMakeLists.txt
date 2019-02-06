cmake_minimum_required(VERSION 3.13)
project(OpenGL_Course)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall")
set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H})
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})
set(SOURCE_FILES main.cpp)

add_executable(OpenGL_Course main.cpp Shader.cpp Shader.h stb_image.h Camera.cpp Camera.h Material.cpp Material.h Material.cpp Material.h lightDirectional.cpp lightDirectional.h LightPoint.cpp LightPoint.h LightSpot.cpp LightSpot.h)
target_link_libraries(OpenGL_Course ${OPENGL_LIBRARY})