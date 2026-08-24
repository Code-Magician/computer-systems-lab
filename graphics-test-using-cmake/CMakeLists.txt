cmake_minimum_required(VERSION 3.20)

project(GraphicsTest
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(GraphicsTest
    src/main.cpp
)

target_link_libraries(GraphicsTest
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)
