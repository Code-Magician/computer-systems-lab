/*
  First Time                                                              : cmake -S . -B build -G Ninja
  Every time we change code file                                          : cmake --build build
  Run above both if changing CMakeLists.txt file.
  For clean build (Remove the build Folder then run above 2 commands)     : rm -rf build
*/


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../../Headers/Shader.h"

using namespace std;

#define WIDTH 1000
#define HEIGHT 600

void process_input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int generate_and_send_triangle_data_to_gpu();
    

int main()
{
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    return -1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  if (glewError != GLEW_OK && glewError != GLEW_ERROR_NO_GLX_DISPLAY)
  {
    cerr << "GLEW error: "
         << glewGetErrorString(glewError)
         << endl;

    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  generate_and_send_triangle_data_to_gpu();
  
  Shader ourShader("/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/1_Getting_Started/src/Shaders/Exercise1/Shaders/vertex.glsl", "/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/1_Getting_Started/src/Shaders/Exercise1/Shaders/fragment.glsl");
  
  while (!glfwWindowShouldClose(window)) {
    // Input
    process_input(window);

    // Rendering
    glClearColor(0.2, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    // Using the Shader Program and rendering the
    ourShader.Use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
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
  glViewport(0, 0, width, height);
}

unsigned int generate_and_send_triangle_data_to_gpu() {
  // Generating Triangle vertex data and sending it to GPU.
  float vertices[] = {0.5f,0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		      -0.5f,0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		      0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Setting Vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  return VAO;
}
