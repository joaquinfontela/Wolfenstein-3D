#ifndef DOOR_H_
#define DOOR_H_

#include "../../common/includes/Map/Map.h"
#include "drawable.h"
#include "clientprotocol.h"
#include <cstring>

class Door : public Drawable {
 public:
  Door(int matrixXCoord, int matrixYCoord, const int& width, const int& height, const int& dx, const int& dy,
       int side, const double& cameraXCoord, const int& i, Map* matrix) :
       Drawable(matrixXCoord, matrixYCoord, DOOR), matrixXCoord(matrixXCoord), matrixYCoord(matrixYCoord), width(width), height(height),
       cameraXCoord(cameraXCoord), dx(dx), dy(dy), side(side), i(i), matrix(matrix) {}
  void draw(TextureManager& manager, double x, double y, double dirX, double dirY,
            double planeX, double planeY, double* distanceBuffer, float diff = 0) override;
  int matrixXCoord, matrixYCoord;
  const int& i;
 private:
  const int& width, height;
  const double& cameraXCoord;
  const int& dx, dy;
  int side;
  Map* matrix;
};

#endif  // DOOR_H_
