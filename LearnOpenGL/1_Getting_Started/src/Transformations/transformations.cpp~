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

#define STB_IMAGE_IMPLEMENTATION
#include "../../Headers/stb_image.h"

using namespace std;

#define WIDTH 1000
#define HEIGHT 600

void process_input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int generate_and_send_triangle_data_to_gpu();
unsigned int loadTexture(string name);
    

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

  unsigned int VAO = generate_and_send_triangle_data_to_gpu();
  
  Shader ourShader("/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/1_Getting_Started/src/Textures/TextureCombined/Shaders/vertex.glsl", "/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/1_Getting_Started/src/Textures/TextureCombined/Shaders/fragment.glsl");

  unsigned int tex1 = loadTexture(
      "/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/"
      "1_Getting_Started/src/Textures/TextureCombined/Brick.jpg");
  unsigned int tex2 = loadTexture(
      "/home/warlock-perry/Documents/computer-systems-lab/LearnOpenGL/"
      "1_Getting_Started/src/Textures/TextureCombined/Doraemon.jpg");

  ourShader.Use();
  ourShader.SetInt("texture1", 0);
  ourShader.SetInt("texture2", 1);
  
  while (!glfwWindowShouldClose(window)) {
    // Input
    process_input(window);

    // Rendering
    glClearColor(0.2, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
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
  float vertices[] = {
      // positions                    // colors                 // texture
      // coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
    0,
    1,
    3,
    1, 2, 3
  };

  unsigned int VBO, VAO, EBO;
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Setting Vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  return VAO;
}

unsigned int loadTexture(string name) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Loading Image Data
  int width, height, numChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(name.c_str(), &width, &height, &numChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cerr << "Texture image Loading Failed" << endl;
  }

  stbi_image_free(data);

  return texture;
}
