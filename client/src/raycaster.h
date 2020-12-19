#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "texturemanager.h"
#include "anglemanager.h"
#include "../../common/includes/Map/Map.h"

#define PI 3.14159265359

class Raycaster {
 public:
  Raycaster(double width, double height, TextureManager& manager, Map& m) : 
          width(width) , height(height) , manager(manager) , matrix(m) {}
  void renderWithPerspective(int x, int y, int viewAngle);
 private:
  double width;
  double height;
  TextureManager& manager;
  Map& matrix;
  double distanceToProyection = floor((width/2)/(tan((PI/2) - PI/3)));
  AngleManager angles;
};

#endif  // RAYCASTER_H_
