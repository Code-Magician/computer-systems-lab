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
unsigned int compile_and_link_shaders();
unsigned int generate_and_send_triangle_data_to_gpu(float vertices[], size_t size);


const char *vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;

void main() {
  gl_Position = vec4(aPos, 1.0);
})";

const char *fragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0, 0.5, 0.2, 1.0);
})";
    

int main()
{
  glfwInit();
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

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  float vertices1[] = {
      -0.95f, -0.5f, 0.0f,

      -0.5f,  0.5f,  0.0f,

      -0.05f, -0.5f, 0.0f,
  };

  float vertices2[] = {
    0.05f,
    -0.5f,
    0.0f,

    0.5f,
    0.5f,
    0.0f,

    0.95f,
    -0.5f,
    0.0f    
    };
  
  unsigned int shaderProgram;
  shaderProgram = compile_and_link_shaders();
  unsigned int VAO1 = generate_and_send_triangle_data_to_gpu(vertices1, sizeof(vertices1));
  unsigned int VAO2 = generate_and_send_triangle_data_to_gpu(vertices2, sizeof(vertices2));  
  
  while (!glfwWindowShouldClose(window)) {
    // Input
    process_input(window);

    // Rendering
    glClearColor(0.2, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Using the Shader Program and rendering the traingle.
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO2);
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

unsigned int compile_and_link_shaders() {
  // Creating and Compiling a simple Vertex Shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Checking if Vertex shader compilation failed
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    cerr << "Error:Shader:Vertex:Compilation_Failed" << endl << infoLog << endl;
  }

  
  // Creating and Compiling a simple Fragment Shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Checking if Fragment Shader compilation failed
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    cerr << "Error:Shader:Fragment:Compilation_Failed" << endl << infoLog << endl;
  }

  
  // Creating Shader Program and Linking both Shaders
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader), glDeleteShader(fragmentShader);  
  
  // Checking if shader program's linking failed
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    cerr << "Error:ShaderProgram:Linking_Failed" << endl << infoLog << endl;
  }

  return shaderProgram;
}

unsigned int generate_and_send_triangle_data_to_gpu(float* vertices, size_t size) {
  // Generating Triangle vertex data and sending it to GPU.
  
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  // Setting Vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return VAO;
}
