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
#include <vector>
#include <cmath>
#include <string>

class cube{
public:
  cube();

  static float vertices[48];
  static unsigned int indices[36];
};

class mapgen{
private: 
  int fillPercent;
  static constexpr int width = 30;
  static constexpr int length = 40;
  static constexpr int height = 20;
  int dstCoords[length][height][width];
  int srcCoords[length][height][width];
  int GetWallCount(int, int, int);
  void SmoothMap();
  void Automata();
  void MapVecs();


public:
  mapgen();
  std::vector<glm::vec3> mapVectors;
  int vecCount;
};