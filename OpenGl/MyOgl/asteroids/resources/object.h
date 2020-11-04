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


class cube{
public:
  cube();
  static float vertices[72];
  static unsigned int indices[60];
  static glm::vec3 positions[7];
};

class bullet{
public:
  bullet();
  static float vertices[48];
  static unsigned int indices[36];
  static glm::vec3 positions[7];
};
