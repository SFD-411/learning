#include "object.h"
#include "indexval.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <memory.h>

// Creates Map Segments
Chunk::Chunk(){
	MapData *MapChunk = new MapData;
  scalar = 16;
  howSmooth = 5;
  noiseThreshold = 21.29f;
  fillCutOff = 81.75f;
  std::vector<int> offset {0, 0, 0};
  MapGeneration(MapChunk, offset);
  CleanUp(MapChunk);
}

void Chunk::CleanUp(MapData *MapChunk){
  delete MapChunk;
}

// Generates weighted noise, averages values and populates vertices based
// on the cutoff during marching cubes indexing.
MapData Chunk::MapGeneration(MapData *MapChunk, std::vector<int> &offset){
  std::vector<float> *newVerts = new std::vector<float>;
  srand(glfwGetTime());
  NoiseGeneration(newVerts);
  for (int smooth = 0; smooth < howSmooth; smooth++){ Smoother(newVerts); }
  March(*newVerts, offset, MapChunk);
  delete newVerts;
  return *MapChunk;
  // Populatevertices(vertices);
}

// Generates random numbers and assigns weighted values 
// to the source index containers based on the noise threshold.
void Chunk::NoiseGeneration(std::vector<float> *newVerts){
  for(int z = 0; z < length; z++){
    for(int y = 0; y < height; y++){
      for(int x = 0; x < width; x++){
        int determinant = (float)(rand() % 100);
        if(determinant >= noiseThreshold){
          newVerts->push_back(determinant);
        } else if (determinant < noiseThreshold) {
          newVerts->push_back(0);
        }
      } 
    } 
  }
}

// Passes grid coordinates to a comparitor to populate the destination index list.
void Chunk::Smoother(std::vector<float> *newVerts){
  std::vector<float> *tempVerts = new std::vector<float>;
  for(int z = 0; z < length; z++){
    for(int y = 0; y < height; y++){
      for(int x = 0; x < width; x++){
        tempVerts->push_back(Cellular(z, y, x, *newVerts));
      }
    }
  }
  *newVerts = *tempVerts;
  delete tempVerts;
}

// takes a set of coordinates, searches their neighboring indices for +/- values
// and creates a ramped average based on the value and the number of neighboring cells.
float Chunk::Cellular(int currentZ, int currentY, int currentX, std::vector<float> &newVerts){
  float cellAvg = 0.0f;
  float cellularCount = 0;
    for(int rangerZ = currentZ - 1; rangerZ <= currentZ + 1; rangerZ++){
      for(int rangerY = currentY - 1; rangerY <= currentY + 1; rangerY++){
        for(int rangerX = currentX - 1; rangerX <= currentX + 1; rangerX++){
          int indexer = (rangerZ * height + rangerY) * width + rangerX;
          if(rangerX >= 0 && rangerX < width &&
             rangerY >= 0 && rangerY < height &&
             rangerZ >= 0 && rangerZ < length){
                cellAvg += newVerts[indexer];
                cellularCount++;
          } else 
          if (currentX == 0 && rangerX == -1 || currentY == 0 && rangerY == -1 || currentZ == 0 && rangerZ == -1 || 
              rangerX == width || rangerY == height || rangerZ == length) {
                cellAvg += noiseThreshold;
          }
        }
      }
    }
  cellAvg = cellAvg / cellularCount;
  return cellAvg;
}

// iterating vertices, creates isovertex positions
// finds the binary value of a cube, and assigns vertexes to indices.
void Chunk::March(std::vector<float> &newVerts, std::vector<int> &offset, MapData *MapChunk){
  int binaryFun = 0;
  MapChunk->indices.clear();
  std::vector<std::vector<float>> *vertexData = new std::vector<std::vector<float>>;
  for(int z = 0; z < length - 1; z+2){
    for(int y = 0; y < height - 1; y+2){
      for(int x = 0; x < width - 1; x+2){
        binaryFun = Cube2Bin(z,y,x, newVerts); // finds binary value of a cube
        if(binaryFun != 0 && binaryFun != 255){
          GenVertexData(binaryFun, (float)z, (float)y, (float)x, *vertexData, MapChunk);
        }
      }
    }
  }
  PopulateVertices(*vertexData, offset, MapChunk);
  CalculateNormals(*vertexData, MapChunk);
  delete vertexData;
}

// turn my cube into a binary index
int Chunk::Cube2Bin(int locZ, int locY, int locX, std::vector<float> &newVerts){
  int binaryVal = 0;
  binaryVal += (1 * EvaluateVertex(locZ, locY, locX, newVerts));
  binaryVal += (2 * EvaluateVertex(locZ, locY, locX + 1, newVerts));
  binaryVal += (4 * EvaluateVertex(locZ + 1, locY, locX + 1, newVerts));
  binaryVal += (8 * EvaluateVertex(locZ + 1, locY, locX, newVerts));
  binaryVal += (16 * EvaluateVertex(locZ, locY + 1, locX, newVerts));
  binaryVal += (32 * EvaluateVertex(locZ, locY + 1, locX + 1, newVerts));
  binaryVal += (64 * EvaluateVertex(locZ + 1, locY + 1, locX + 1, newVerts));
  binaryVal += (128 * EvaluateVertex(locZ + 1, locY + 1, locX, newVerts));
  return binaryVal;
}

 // Returns a 1 or 0 value for valid coordinates
int Chunk::EvaluateVertex(int z, int y, int x, std::vector<float> &newVerts){
  int indexer = (z * height + y) * width + x;
  if (newVerts[indexer] < fillCutOff){
    return 1;
  } else {
    return 0;
  }
}

 // Creates Vertex and Index listing simultaneously.
void Chunk::GenVertexData(int bIndex, float locZ, float locY, float locX, std::vector<std::vector<float>> &vertexData, MapData *MapChunk){
	std::vector<float> *tempVecs = new std::vector<float>;
  int indexCount = 0;
  int vectorIndex = 0;
  while (indexTable[bIndex][indexCount] != -1){
    switch(indexTable[bIndex][indexCount]){
      case 0:  // // find the isoverts between 0 and 1
        tempVecs->push_back(Isovert(locX));
        tempVecs->push_back(locY);
        tempVecs->push_back(locZ);
        break;
      case 1: // // find the isoverts between 1 and 2
        tempVecs->push_back(locX + 1);
        tempVecs->push_back(locY);
        tempVecs->push_back(Isovert(locZ));
        break;
      case 2: // // find the isoverts between 2 and 3
        tempVecs->push_back(Isovert(locX));
        tempVecs->push_back(locY);
        tempVecs->push_back(locZ + 1);
        break;
      case 3: // // find the isoverts between 3 and 0 
        tempVecs->push_back(locX);
        tempVecs->push_back(locY);
        tempVecs->push_back(Isovert(locZ));
        break;
      case 4: // // find the isoverts between 4 and 5
        tempVecs->push_back(Isovert(locX));
        tempVecs->push_back(locY + 1);
        tempVecs->push_back(locZ);
        break;
      case 5: // // find the isoverts between 5 and 6
        tempVecs->push_back(locX + 1);
        tempVecs->push_back(locY + 1);
        tempVecs->push_back(Isovert(locZ));
        break;
      case 6: // // find the isoverts between 6 and 7
        tempVecs->push_back(Isovert(locX));
        tempVecs->push_back(locY + 1); 
        tempVecs->push_back(locZ + 1);
        break;
      case 7: // // find the isoverts between 7 and 4
        tempVecs->push_back(locX);
        tempVecs->push_back(locY + 1);
        tempVecs->push_back(Isovert(locZ));
        break;
      case 8: // // find the isoverts between 0 and 4
        tempVecs->push_back(locX);
        tempVecs->push_back(Isovert(locY));
        tempVecs->push_back(locZ);
        break;
      case 9: // // find the isoverts between 1 and 5
        tempVecs->push_back(locX + 1);
        tempVecs->push_back(Isovert(locY));
        tempVecs->push_back(locZ);
        break;
      case 10: // // find the isoverts between 2 and 6
        tempVecs->push_back(locX + 1);
        tempVecs->push_back(Isovert(locY));
        tempVecs->push_back(locZ + 1);
        break;
      case 11: // // find the isoverts between 0 and 7
        tempVecs->push_back(locX);
        tempVecs->push_back(Isovert(locY));
        tempVecs->push_back(locZ + 1);
        break;
      }
        auto vectIt = std::find(vertexData.begin(), vertexData.end(), *tempVecs);      // find the calculated vertex
        if (vectIt != vertexData.end()){                                                    // if it's in the list
          vectorIndex = std::distance(vertexData.begin(), vectIt);                                // get the index
          MapChunk->indices.push_back(vectorIndex);                                                         // add it to the indices list
        } else if (vectIt == vertexData.end()) {                                            // if it's not in the list
          vertexData.push_back(*tempVecs);                                                        // add it to the vertex list
          auto vectIt = std::find(vertexData.begin(), vertexData.end(), *tempVecs);               // find the vertex
          vectorIndex = std::distance(vertexData.begin(), vectIt);                                // get the index
          MapChunk->indices.push_back(static_cast<unsigned int>(vectorIndex));                              // add it to the indices list
        }
        tempVecs->clear();
        indexCount++;
  }
  delete tempVecs;
}

 // Finds the midpoint between two vertex locations.
float Chunk::Isovert(float V){  
  return ((V + (V + 1)) / 2);
}

 // Populates Vertex Coords and Color vectors.
void Chunk::PopulateVertices(std::vector<std::vector<float>> &vertexData, std::vector<int> &offset, MapData *MapChunk){
  MapChunk->vertices.clear();
  for(int i = 0; i < vertexData.size(); i++){
    float colorvar = (float)(rand() % 33);

    if( colorvar < 16.5 ){ colorvar = colorvar / 100.0f; } 
    else { colorvar = (colorvar / 100.0f) * 2.0f; }

    MapChunk->vertices.push_back((vertexData[i][0] * scalar) + (float)(offset[0] * mapChunkSize));
    MapChunk->vertices.push_back((vertexData[i][1] * scalar) + (float)(offset[1] * mapChunkSize));
    MapChunk->vertices.push_back((vertexData[i][2] * scalar) + (float)(offset[2] * mapChunkSize));
    MapChunk->colors.push_back(vertexData[i][1] / height);
    MapChunk->colors.push_back(vertexData[i][1] / (height + 10) * colorvar);
    MapChunk->colors.push_back(colorvar / (vertexData[i][1] + 0.2f));
  }
}

 // Finds the coordinates of vertices based on index, and calculates normal directions.
void Chunk::CalculateNormals(std::vector<std::vector<float>> &vertexData, MapData *MapChunk){
   MapChunk->normals.clear();

   for (int i = 0; i < MapChunk->indices.size() / 3; i++){
    i = i * 3;
    std::vector<float> p1 = vertexData[MapChunk->indices[i]];
    std::vector<float> p2 = vertexData[MapChunk->indices[i + 1]];
    std::vector<float> p3 = vertexData[MapChunk->indices[i + 2]];

    std::vector<float> U = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
    std::vector<float> V = {p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]};

    MapChunk->normals.push_back((U[1] * V[2]) - (U[2] * V[1]));
    MapChunk->normals.push_back((U[2] * V[0]) - (U[0] * V[2]));
    MapChunk->normals.push_back((U[0] * V[1]) - (U[1] * V[0]));
  }
  // return normals;
}



// World::TerrainChunk::TerrainChunk(glm::vec3 coordinates, int size){ 
//   chunkPosition = glm::vec3(coordinates.x * size, coordinates.y * size, coordinates.z * size);
//   MapData *MapChunk = new MapData;
//   *MapChunk = MapGen.MapGeneration();
//   MapGen.CleanUp();
//   return;  }




World::World(){ 
  chunkSize = MapGen.mapChunkSize;
  visibleChunks = maxFOV / chunkSize;
  return ; }


void World::UpdateChunks(glm::vec3 &playerLoc){
  // take user input and find current grid squares

  currentChunk[2] = (int)playerLoc.x/chunkSize;
  currentChunk[1] = (int)playerLoc.y/chunkSize;
  currentChunk[0] = (int)playerLoc.z/chunkSize;

  if (previousChunk != currentChunk){
  // find which chunks are visible
    std::vector<int> chunkRegion;
    for (int zCount = -visibleChunks; zCount <= visibleChunks; zCount++){
      for (int yCount = -visibleChunks; yCount <= visibleChunks; yCount++){
        for (int xCount = -visibleChunks; xCount <= visibleChunks; xCount++){
          chunkRegion.push_back(currentChunk[2] - xCount);
          chunkRegion.push_back(currentChunk[1] - yCount);
          chunkRegion.push_back(currentChunk[0] + zCount);
          if(MapTable.count(chunkRegion)){
            // MapData *currentChunk = new MapData;
            // *currentChunk = MapTable.at(chunkRegion);
            // delete currentChunk;
          } else {
            MapData *newChunk = new MapData;
            *newChunk = MapGen.MapGeneration(newChunk, chunkRegion);
            newChunk->MapChunkCoord = chunkRegion;
            ChunkData = *newChunk; 
            delete newChunk;
          }
        chunkRegion.clear();                           
        }
      }
    }
    previousChunk[0] = currentChunk[0];
    previousChunk[1] = currentChunk[1];
    previousChunk[2] = currentChunk[2];
  }
}

