#include "object.h"

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


cube::cube(){  return; };
float cube::vertices[] = {
  -0.5f, -1.5f, -0.5f, 0.7f, 0.3f, 0.0f, // 0 left - bottom - back
   0.5f, -1.5f, -0.5f, 0.7f, 0.3f, 0.0f, // 1 right - bottom - back - BLUE
  -0.5f,  1.5f, -0.5f, 0.0f, 0.5f, 0.7f, // 2 left - top - back - RED
   0.5f,  1.5f, -0.5f, 0.0f, 0.5f, 0.7f, // 3 right - top - back - BLUE
  -0.5f, -1.5f, 0.5f, 0.7f, 0.3f, 0.0f, // 4 left - bottom - front - GREEN
   0.5f, -1.5f, 0.5f, 0.7f, 0.3f, 0.0f, // 5 right - bottom - front - GREEN
  -0.5f,  1.5f, 0.5f, 0.0f, 0.5f, 0.7f, // 6 left - top - front - RED
   0.5f,  1.5f, 0.5f, 0.0f, 0.5f, 0.7f // 7 right - top - front
};
unsigned int cube::indices[] = {
  0, 1, 2,
  2, 3, 0,
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

mapgen::mapgen(){  
  fillPercent = 13;
  vecCount = 0;
  srcCoords[length][height][width];
  dstCoords[length][height][width];
  MapVecs();
  };

/* Initializes positions based on random values and groups
  the indices based on positional weighting */
void mapgen::MapVecs(){
  // generates random values and cores an index based on the fill percentage.
  srand(glfwGetTime());
  for (int z = 0; z < length; z++){
    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++){
        if((rand() % 100 < fillPercent) || x < 1 || x >= width - 1 || y < 1 || y >= height - 1 || z < 1 || z >= length -1){
         srcCoords[z][y][x] = 1;
        } else {
         srcCoords[z][y][x] = 0;
        }
      }
    }
  }

  for (int i = 0; i < 5; i++){
    SmoothMap();
    Automata();
  }
  
  // transfers valid mapped coordinates to an index vector as floats 
  for (int z = 0; z < length; z++){
   for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      if(srcCoords[z][y][x] != 0){
        vecCount++;
        mapVectors.push_back(glm::vec3(x, y, z));
      }
    }
   }
  }

};

/* Counts the source coordinates weighted values,
   and appends them to the destination coordinates */
void mapgen::SmoothMap(){
  for (int z = 0; z < length; z++){
    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++){
        int wallTiles = GetWallCount(x, y, z);
        if (wallTiles > 4){
         dstCoords[z][y][x] = 1;
        } else if (wallTiles < 4) {
         dstCoords[z][y][x] = 0;
        }
      }
    }
  }
};

// Counts the an index value based on the neighboring source coordinates
int mapgen::GetWallCount(int coordX, int coordY, int coordZ){
  int wallCount = 0;
  for (int localZ = coordZ - 1; localZ <= coordZ + 1; localZ++){
   for (int localY = coordY - 1; localY <= coordY + 1; localY++){
    for (int localX = coordX - 1; localX <= coordX + 1; localX++){
      if (localX >= 0 && localX < width && localY >= 0 && localY < height && localZ >=0 && localZ < length){
        if(localY != coordY || localX != coordX || localZ != coordZ){
          wallCount += srcCoords[localZ][localY][localX];
        } else {
          wallCount++; 
        }
      }
    }
   }
  }
  return wallCount;
};

// Replaces original source coordinates with smoothed destination coordinates.
void mapgen::Automata(){
  for (int z = 0; z < length; z++){
    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++){
        srcCoords[z][y][x] = dstCoords[z][y][x];
     }
    }
  }
}


