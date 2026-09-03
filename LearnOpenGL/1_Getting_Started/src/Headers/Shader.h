#ifndef SHADER_H
#define SHADER_H

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
public:
  unsigned int ID;

  Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        
    try {
      vShaderFile.open(vertexShaderPath);
      fShaderFile.open(fragmentShaderPath);

      if (!vShaderFile.is_open()) {
	cerr << "ERROR::FILE_NOT_OPENED" << endl << vertexShaderPath << endl;
      }

      if (!fShaderFile.is_open()) {
        cerr << "ERROR::FILE_NOT_OPENED" << endl << fragmentShaderPath << endl;
      }

      stringstream vShaderStream, fShaderStream;
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    } catch (ifstream::failure e) {
      cout << "ERROR::SHADER::FILE_NOT_READ" << e.what() << endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Compile Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infoLog << endl;
    }

    // Compile Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl << infoLog << endl;
    }

    // Link Shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      cerr << "SHADER::ERROR::SHADERPROGRAM::LINK_FAILED" << endl << infoLog << endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  void Use() {
    glUseProgram(ID);
  }

  void SetBool(const string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void SetInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);  
  }
  void SetFloat(const string &name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);  
  }
};

#endif
