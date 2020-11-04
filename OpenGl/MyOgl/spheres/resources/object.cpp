#include "object.h"

#include <glm/glm.hpp>
#include <math.h>

FiboSphere::FiboSphere() { return; };

void FiboSphere::populateSphere (){
  tau = 2 * M_PI;
  goldenRatio = (sqrt (5) / 2);
  angleValue = tau * goldenRatio + 1;
  for(int i = 0; i < points; i++){
    float t = (float) i / points;
    float angle1 = acos (1 - 2 * t);
    float angle2 = angleValue * i;
    vertex[i].x = sin (angle1) * cos (angle2);
    vertex[i].y = sin (angle1) * sin (angle2);
    vertex[i].z = cos (angle1);
  }
};
