#include "raycaster.h"

#include <climits>
#include <algorithm>
#include <vector>
#include <math.h>

#include "drawable.h"
#include <iostream>
void Raycaster::run(){

  while(alive){
    this->window->fillWolfenstein();

    double dirX = this->player->dirX;
    double dirY = this->player->dirY;
    double posX = this->player->x;
    double posY = this->player->y;
    double planeX = this->player->planeX;
    double planeY = this->player->planeY;

    double zBuffer[this->width];
    for(int x = 0; x < this->width; x++) {

      double cameraX = 2 * x / (double)this->width - 1;
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

      int mapX = int(posX);
      int mapY = int(posY);

      double sideDistX;
      double sideDistY;

      double deltaDistX = std::abs(1 / rayDirX);
      double deltaDistY = std::abs(1 / rayDirY);
      double perpWallDist;

      int stepX;
      int stepY;

      int hit = 0;
      int side;

      if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }

      if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

      while (hit == 0) {
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }

        if (mapX >= matrix.dimx || mapY >= matrix.dimy || mapX < 0 || mapX < 0) {
          mapX = INT_MAX;
          mapY = INT_MAX;
        }

        if(matrix.get(mapX,mapY) > 0) hit = 1;
      }

      if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;


      int lineHeight = (int) (this->height/ perpWallDist);
      int offset = 0;

      int texNum = matrix.get(mapX,mapY);

      double wallX;
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      int texX = int(wallX * double(64));
      if(side == 0 && rayDirX > 0) texX = 64 - texX - 1;
      if(side == 1 && rayDirY < 0) texX = 64 - texX - 1;

      if (side == 0) {
         offset = int(sideDistX) % 64;
      } else {
         offset = int(sideDistY) % 64;
      }

      Area destArea(x, (this->height - lineHeight) / 2, 1, lineHeight);
      Area srcArea(texX, 0, 1, lineHeight);


      this->manager.render(texNum, srcArea, destArea);

      zBuffer[x] = perpWallDist;
    }

    for (Drawable* d : this->sprites) {
      d->loadDistanceWithCoords(posX, posY);
    }

    std::sort(this->sprites.begin(), this->sprites.end());


    for (Drawable* d : this->sprites) {
      d->draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer);
    }

  this->window->render();
  }
}
