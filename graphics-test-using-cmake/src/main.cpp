/*
  First Time                                                              : cmake -S . -B build -G Ninja
  Every time we change code file                                          : cmake --build build
  Run above both if changing CMakeLists.txt file.
  For clean build (Remove the build Folder then run above 2 commands)     : rm -rf build
*/


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main()
{
    // -------------------------
    // Initialize GLFW
    // -------------------------
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // -------------------------
    // OpenGL 3.3 Core Profile
    // -------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // -------------------------
    // Create Window
    // -------------------------
    GLFWwindow* window =
        glfwCreateWindow(
            1000,
            800,
            "Graphics Test",
            nullptr,
            nullptr
        );

    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // -------------------------
    // Make OpenGL Context Current
    // -------------------------
    glfwMakeContextCurrent(window);

    // -------------------------
    // Initialize GLEW
    // -------------------------
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

    if (err != GLEW_OK) {

        cerr << "GLEW warning: "
             << glewGetErrorString(err)
             << " (error code " << err << ")"
             << endl;

        // IMPORTANT:
        // We DO NOT return here.
        //
        // GLEW can report a GLX-related error under
        // Wayland/EGL even though the OpenGL context
        // itself is valid.
    }

    // -------------------------
    // Print OpenGL Information
    // -------------------------
    cout << "OpenGL Version: "
         << glGetString(GL_VERSION)
         << endl;

    cout << "OpenGL Renderer: "
         << glGetString(GL_RENDERER)
         << endl;

    cout << "OpenGL Vendor: "
         << glGetString(GL_VENDOR)
         << endl;

    // -------------------------
    // Main Loop
    // -------------------------
    while (!glfwWindowShouldClose(window)) {

        glClearColor(
            0.1f,
            0.2f,
            0.3f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // -------------------------
    // Cleanup
    // -------------------------
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
