#ifndef DOOR_H_
#define DOOR_H_

#include "drawable.h"
#include "clientprotocol.h"
#include <cstring>

class Door : public Drawable {
 public:
  Door(int mapX, int mapY, int width, int height, int stepX, int stepY, int side, double cameraX) :
       Drawable(mapX, mapY, DOOR), mapX(mapX), mapY(mapY), width(width),
       height(height), cameraX(cameraX), stepX(stepX), stepY(stepY), side(side) {}
  void openDoor();
  void draw(TextureManager& manager, double posX, double posY, double dirX,
    double dirY, double planeX, double planeY, double* zBuffer) override;
  int mapX, mapY;
private:
  int width, height;
  double cameraX;
  int stepX, stepY;
  int side;
};

#endif  // DOOR_H_
