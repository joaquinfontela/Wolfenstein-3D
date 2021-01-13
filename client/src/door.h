#ifndef DOOR_H_
#define DOOR_H_

#include "../../common/includes/Map/Map.h"
#include "drawable.h"
#include "clientprotocol.h"
#include <cstring>

class Door : public Drawable {
 public:
  Door(int mapX, int mapY, const int& width, const int& height, const int& stepX, const int& stepY,
       int side, const double& cameraX, const int& x, Map* matrix) :
       Drawable(mapX, mapY, DOOR), mapX(mapX), mapY(mapY), width(width),height(height),
       cameraX(cameraX), stepX(stepX), stepY(stepY), side(side), x(x), matrix(matrix), dx(0) {}
  void openDoor();
  void draw(TextureManager& manager, double posX, double posY, double dirX,
    double dirY, double planeX, double planeY, double* zBuffer) override;
  int mapX, mapY;
  const int& x;
private:
  int dx;
  const int& width, height;
  const double& cameraX;
  const int& stepX, stepY;
  int side;
  Map* matrix;
};

#endif  // DOOR_H_
