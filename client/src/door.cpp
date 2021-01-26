#include "door.h"
#include "area.h"
#include "texturemanager.h"
#include <iostream>

void Door::draw(TextureManager& manager, double posX, double posY, double dirX,
  double dirY, double planeX, double planeY, double* zBuffer, float diff) {

  char doorState = this->matrix->getDoorState(this->mapX, this->mapY);
  if (doorState == OPEN) return;

  float time = this->matrix->doors[this->mapX][this->mapY].timer;
  double rayDirX = dirX + planeX * cameraX;
  double rayDirY = dirY + planeY * cameraX;

  bool isSide = (this->side == 0);
  double perpWallDist = (isSide * (this->mapX - posX + ((1 - stepX) >> 1)) / (rayDirX)) +
                        (!isSide * (this->mapY - posY + ((1 - stepY) >> 1)) / (rayDirY));
  double wallX = (isSide * (posY + perpWallDist * rayDirY)) +
                 (!isSide * (posX + perpWallDist * rayDirX));
  wallX -= floor((wallX));

  int texX = int(wallX * double(BLOCKSIZE));
  bool condition = ((isSide && rayDirX > 0) || (!isSide && rayDirY < 0));
  texX = (BLOCKSIZE - texX - 1) * condition + texX * (!condition);
  if (texX < BLOCKSIZE * (1 - time)) return;
  int lineHeight = int(this->height / perpWallDist);

  if (doorState == CLOSED) {
    Area srcArea(texX, 0, 1, (lineHeight < BLOCKSIZE) ? BLOCKSIZE : lineHeight);
    Area destArea(x, (this->height - lineHeight) >> 1, 1, lineHeight);
    manager.render(DOOR, srcArea, destArea);
  } else {
    Area srcArea(texX - BLOCKSIZE * (1 - time), 0, 1, (lineHeight < BLOCKSIZE) ? BLOCKSIZE : lineHeight);
    Area destArea(x, (this->height - lineHeight) >> 1, 1, lineHeight);
    manager.render(DOOR, srcArea, destArea);
  }

  if(perpWallDist < zBuffer[x]) zBuffer[x] = perpWallDist;
}
