#include "door.h"
#include "area.h"
#include "texturemanager.h"
#include <iostream>

void Door::draw(TextureManager& manager, double posX, double posY, double dirX,
  double dirY, double planeX, double planeY, double* zBuffer) {
  char doorState = this->matrix->getDoorState(this->mapX, this->mapY);

  if (doorState == OPEN) return;

  float time = this->matrix->doors[this->mapX][this->mapY].timer;
  double rayDirX = dirX + planeX * cameraX;
  double rayDirY = dirY + planeY * cameraX;

  bool isSide = (this->side == 0);
  double perpWallDist = ((this->mapX - posX + ((1 - stepX) >> 1)) / (rayDirX) * isSide) +
                        ((this->mapY - posY + ((1 - stepY) >> 1)) / (rayDirY) * !isSide);
  double wallX = ((posY + perpWallDist * rayDirY) * isSide) +
                 ((posX + perpWallDist * rayDirX) * !isSide);
  wallX -= floor((wallX));

  int texX = int(wallX * double(BLOCKSIZE));
  if( isSide && rayDirX > 0) texX = BLOCKSIZE - texX - 1;
  if(!isSide && rayDirY < 0) texX = BLOCKSIZE - texX - 1;
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
