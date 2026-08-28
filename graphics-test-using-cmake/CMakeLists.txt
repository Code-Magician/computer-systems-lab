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

# Making render_window.cpp executable
add_executable(RenderWindow
    src/render_window.cpp
)

target_link_libraries(RenderWindow
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)

# Making render_triangle.cpp executable
add_executable(RenderTriangle
    src/render_triangle.cpp
)

target_link_libraries(RenderTriangle
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)

# Making render_rectangle.cpp executable
add_executable(RenderRectangle
    src/render_rectangle.cpp
)

target_link_libraries(RenderRectangle
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)


# Exercise-1 (Render 2 Triangles)
add_executable(Exercise1
    src/render_2_triangles_exercise.cpp
)

target_link_libraries(Exercise1
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)

# Exercise-2 (Render 2 Triangles with different VAO's and VBO's)
add_executable(Exercise2
    src/render_2_triangles_exercise_2.cpp
)

target_link_libraries(Exercise2
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)

# Exercise-3 (Render 2 Triangles with different Fragment Shader such that one triangle's color is yellow)
add_executable(Exercise3
    src/render_2_triangles_exercise_3.cpp
)

target_link_libraries(Exercise3
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)
