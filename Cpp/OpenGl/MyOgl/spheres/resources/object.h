#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <math.h>


class FiboSphere {
public:
  FiboSphere();
  void populateSphere();
  glm::vec3 vertex[32];

private:
  const unsigned int points = 32;
  float tau;
  float goldenRatio;
  float angleValue;
};
