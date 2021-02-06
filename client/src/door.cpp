#include "../includes/door.h"

#include <iostream>

#include "../includes/area.h"
#include "../includes/texturemanager.h"

void Door::draw(TextureManager& manager, double x, double y, double dirX,
                double dirY, double planeX, double planeY,
                double* distanceBuffer, float diff) {
  char doorState =
      this->matrix->getDoorState(this->matrixXCoord, this->matrixYCoord);
  if (doorState == OPEN) return;

  float time = this->matrix->getTimers(this->matrixXCoord, this->matrixYCoord);

  double rayDirX = dirX + planeX * cameraXCoord;
  double rayDirY = dirY + planeY * cameraXCoord;

  bool isSide = (this->side == 0);
  double perpendicularWallDistance =
      (isSide * (this->matrixXCoord - x + ((1 - dx) >> 1)) / (rayDirX)) +
      (!isSide * (this->matrixYCoord - y + ((1 - dy) >> 1)) / (rayDirY));
  double wallX = (isSide * (y + perpendicularWallDistance * rayDirY)) +
                 (!isSide * (x + perpendicularWallDistance * rayDirX));
  wallX -= floor((wallX));

  int doorStripe = int(wallX * double(BLOCKSIZE));
  bool condition = ((isSide && rayDirX > 0) || (!isSide && rayDirY < 0));
  doorStripe =
      (BLOCKSIZE - doorStripe - 1) * condition + doorStripe * (!condition);
  if (doorStripe < BLOCKSIZE * (1 - time)) return;
  int wallHeight = int(this->height / perpendicularWallDistance);

  bool tooFar = (wallHeight < BLOCKSIZE);
  if (doorState == CLOSED) {
    Area srcArea(doorStripe, 0, 1, tooFar * BLOCKSIZE + !tooFar * wallHeight);
    Area destArea(i, (this->height - wallHeight) >> 1, 1, wallHeight);
    manager.render(this->matrix->get(matrixXCoord, matrixYCoord), srcArea, destArea);
  } else {
    Area srcArea(doorStripe - BLOCKSIZE * (1 - time), 0, 1,
                 tooFar * BLOCKSIZE + !tooFar * wallHeight);
    Area destArea(i, (this->height - wallHeight) >> 1, 1, wallHeight);
    manager.render(this->matrix->get(matrixXCoord, matrixYCoord), srcArea,
                   destArea);
  }

  if (perpendicularWallDistance < distanceBuffer[i])
    distanceBuffer[i] = perpendicularWallDistance;
}
