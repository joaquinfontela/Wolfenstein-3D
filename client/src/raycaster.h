#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "texturemanager.h"
#include "anglemanager.h"
#include "../../common/includes/Map/Map.h"
#include "player.h"
#include "../../common/includes/Thread/Thread.h"

#define PI 3.14159265359

class Raycaster : public Thread {
 public:
  Raycaster(double width, double height, TextureManager& manager, Map& m, Player* p) : 
          width(width) , height(height) , manager(manager) , matrix(m) , self(p) {}
  void run();
 private:
  double width;
  double height;
  TextureManager& manager;
  Map& matrix;
  Player* self;
  double distanceToProyection = floor((width/2)/(tan((PI/2) - PI/3)));
  AngleManager angles;
};

#endif  // RAYCASTER_H_
