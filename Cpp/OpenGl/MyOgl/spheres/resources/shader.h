#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

  int result;
  int length;
  int success;
  std::string line;
  std::stringstream ss[2];

  struct ShaderSource{
    std::string VertexSource;
    std::string FragmentSource;
  };

  enum class ShaderType{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  };

static unsigned int compileShader(unsigned int type, const std::string& sourcecode){
  unsigned int id = glCreateShader(type);
  const char* src = sourcecode.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed "
              << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
              << " Shader Compilation!" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }
  return id;
}

static ShaderSource parseShader(const std::string& filepath){
  std::ifstream stream(filepath);
  ShaderType type = ShaderType::NONE;
  while (getline(stream, line)){
    if (line.find("#Shader") != std::string::npos)
    {
      if(line.find("Vertex") != std::string::npos)
      {
        type = ShaderType::VERTEX;
      }
      else if (line.find("Fragment") != std::string::npos)
      {
        type = ShaderType::FRAGMENT;
      }
    }
    else
    {
    ss[(int)type] << line << '\n';
    }
  }
  return{ss[0].str(), ss[1].str()};
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader, unsigned int& program){
  unsigned int vert = compileShader(GL_VERTEX_SHADER, vertexShader);
  glAttachShader(program, vert);
  unsigned int frag = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
  glAttachShader(program, frag);
  glLinkProgram(program);
  glValidateProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  char* infoLog = (char*)alloca(success * sizeof(char));
  if (!success)
  {
      glGetProgramInfoLog(program, success, NULL, infoLog);
      std::cout << "Creating Shader Failed\n" << infoLog << std::endl;
  }
  glDeleteShader(vert);
  glDeleteShader(frag);
  return program;
}
