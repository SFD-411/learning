#include "object.h"

#include <glm/glm.hpp>
#include <math.h>

cube::cube(){  return; };
  float cube::vertices[] = {
    -0.5f,  0.7f, -0.5f, 0.7f, 0.0f, 0.0f, // 0 left - top - back - RED
     0.5f,  0.7f, -0.5f, 0.0f, 0.0f, 0.7f, // 1 right - top - back - BLUE
     0.5f,  0.7f, 0.5f, 0.3f, 0.3f, 0.3f, // 2 right - top - front
    -0.5f,  0.7f, 0.5f, 0.7f, 0.0f, 0.0f, // 3 left - top - front - RED

    -0.0f,  0.0f, -0.7f, 0.7f, 0.0f, 0.0f, // 4 center - middle - back - RED
    -0.7f,  0.0f, 0.0f, 0.7f, 0.0f, 0.0f, // 5 right - middle - RED
     0.0f,  0.0f, 0.7f, 0.3f, 0.3f, 0.3f, // 6 center - middle - front
    -0.7f,  0.0f, -0.0f, 0.0f, 0.0f, 0.7f, // 7 left - middle - BLUE

    -0.5f, -0.7f, -0.5f, 0.3f, 0.3f, 0.3f, // 8 left - bottom - back
     0.5f, -0.7f, -0.5f, 0.0f, 0.0f, 0.7f, // 9 right - bottom - back - BLUE
     0.5f, -0.7f, 0.5f, 0.0f, 0.7f, 0.0f, // 11 right - bottom - front - GREEN
    -0.5f, -0.7f, 0.5f, 0.0f, 0.7f, 0.0f // 10 left - bottom - front - GREEN
  };
  unsigned int cube::indices[] = {
    10, 11, 8, 
    8, 9, 10, 
    11, 10, 6, 
    11, 6, 7, 
    8, 11, 7, 
    8, 7, 4, 
    9, 8, 4, 
    9, 4, 5, 
    9, 5, 10,
    10, 5, 6,
    6, 5, 2,
    2, 3, 6,
    6, 3, 7,
    3, 0, 7,
    7, 0, 4,
    4, 0, 1,
    5, 1, 2,
    0, 3, 2,
    2, 1, 0
  };
  glm::vec3 cube::positions[] = {
    glm::vec3( 0.0f,  -1.0f,  1.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -3.2f, -2.5f),
    glm::vec3(-6.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -4.0f, -4.5f)
  };


bullet::bullet(){  return; };
  float bullet::vertices[] = {
    -0.02f, -0.02f, -0.5f, 1.0f, 0.3f, 0.7f, // 0 left - bottom - back
     0.02f, -0.02f, -0.5f, 1.0f, 0.3f, 0.7f, // 1 right - bottom - back
    -0.02f,  0.02f, -0.5f, 1.0f, 0.3f, 0.7f, // 2 left - top - back
     0.02f,  0.02f, -0.5f, 1.0f, 0.3f, 0.7f, // 3 right - top - back
    -0.02f, -0.02f, 0.5f, 1.0f, 0.3f, 0.7f, // 4 left - bottom - front
     0.02f, -0.02f, 0.5f, 1.0f, 0.3f, 0.7f, // 5 right - bottom - front
    -0.02f,  0.02f, 0.5f, 1.0f, 0.3f, 0.7f, // 6 left - top - front
     0.02f,  0.02f, 0.5f, 1.0f, 0.3f, 0.7f // 7 right - top - front
  };
  unsigned int bullet::indices[] = {
    0, 1, 2,
    3, 2, 1,
    0, 1, 4,
    5, 4, 1,
    0, 4, 2,
    6, 2, 4,
    6, 2, 7,
    3, 7, 2,
    3, 1, 5,
    7, 5, 3,
    5, 4, 7,
    6, 7, 4
  };

