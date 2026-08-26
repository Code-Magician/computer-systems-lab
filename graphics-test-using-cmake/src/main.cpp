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

#define WIDTH 1000
#define HEIGHT 600

void process_input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Graphics OpenGL Test", NULL, NULL);

  if (window == NULL) {
    cerr << "Failed to create the GLFW window." << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  GLenum glewError = glewInit();

  if (glewError != GLEW_OK)
  {
    cerr << "GLEW error: "
         << glewGetErrorString(glewError)
         << endl;

    glfwTerminate();
    return -1;
  }
  
  if (glewInit() != GLEW_OK) {
    cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glViewport(0, 0, WIDTH * 0.8, HEIGHT * 0.8);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    // Input
    process_input(window);

    // Rendering
    glClearColor(0.2, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Call Events and Swap Buffers
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  glfwTerminate();
  
  return 0;
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width * 0.8, height * 0.8);
}
