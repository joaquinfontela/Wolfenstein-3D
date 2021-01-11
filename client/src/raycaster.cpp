#include "raycaster.h"
#include "drawable.h"
#include "clientprotocol.h"
#include <climits>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
#include <time.h>

static bool isDoor(int id){
  return (id == 20); // Expand to list of id's.
}

void Raycaster::run(){

  auto t1 = std::chrono::steady_clock::now();

  int iters = 0;
  while(alive){

    this->window->fillWolfenstein();

    double dirX = this->player->dirX;
    double dirY = this->player->dirY;
    double posX = this->player->x;
    double posY = this->player->y;
    double planeX = this->player->planeX;
    double planeY = this->player->planeY;

    double zBuffer[this->width];
    Door door;
    for(int x = 0; x < this->width; x++) {
      door.hit = false;

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

        if (mapX >= matrix.dimx || mapY >= matrix.dimy || mapX < 0 || mapY < 0) {
          mapX = INT_MAX;
          mapY = INT_MAX;
          hit = 1;
        } else if (matrix.get(mapX,mapY) > 0) {
          if (isDoor(matrix.get(mapX, mapY)) /*&& door.mapX != mapX && door.mapY != mapY*/){
            door(mapX, mapY, side);
            door.calcDistToWall(posX, posY, stepX, stepY, rayDirX, rayDirY);
            continue;
          }
          hit = 1;
        }
      }

      std::cout << side << std::endl;
      if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      int lineHeight = int(this->height/ perpWallDist);

      int texNum = 1;
      if (mapY != INT_MAX) {
        texNum = matrix.get(mapX,mapY);
      }

      double wallX;
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      int texX = int(wallX * double(BLOCKSIZE));
      if(side == 0 && rayDirX > 0) texX = BLOCKSIZE - texX - 1;
      if(side == 1 && rayDirY < 0) texX = BLOCKSIZE - texX - 1;

      if (!door.hit) {
        Area srcArea(texX, 0, 1, (lineHeight < BLOCKSIZE) ? BLOCKSIZE : lineHeight);
        Area destArea(x, (this->height - lineHeight) / 2, 1, lineHeight);
        this->manager.render(texNum, srcArea, destArea);
      } else { // DOOR
        std::cout << "tu puta madre\n";
        lineHeight = int(this->height/door.perpWallDist);
        if (side == 0) wallX = posY + door.perpWallDist * rayDirY;
        else wallX = posX + door.perpWallDist * rayDirX;
        wallX -= floor((wallX));
        texX = int(wallX * double(BLOCKSIZE));
        Area srcArea(texX, 0, 1, (lineHeight < BLOCKSIZE) ? BLOCKSIZE : lineHeight);
        Area destArea(x, (this->height - lineHeight) / 2, 1, lineHeight);
        this->manager.render(texNum, srcArea, destArea);
      }
      zBuffer[x] = perpWallDist;
    }

    this->lock.lock();
    for (Drawable* d : this->sprites) { d->loadDistanceWithCoords(posX, posY); }
    std::sort(this->sprites.begin(), this->sprites.end(), []
      (Drawable* a, Drawable* b) -> bool { return *a < *b; });
    for (Drawable* d : this->sprites) { d->draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer); }
    this->lock.unlock();

    Area d2(0, 0, this->width, this->height);
    this->manager.renderAll(HUD_SPRITE, d2);

    auto t2 = std::chrono::steady_clock::now();

    #ifdef FPS_FREQ
    #define FPS_FREQ 50
    //Use this with a VM only case.

    if (!(iters % FPS_FREQ)) {
      std::chrono::duration<float,std::milli> diff = t2 - t1;
      if (!iters) this->hud.updateFpsCounter((1000)/ceil(diff.count()));
      else this->hud.updateFpsCounter((FPS_FREQ * 1000)/ceil(diff.count()));
      t1 = t2;
    }
    if (!(iters % FPS_FREQ)) this->hud.updateBjFace();

    #endif

    this->hud.update();
    this->window->render();
    iters++;
  }
}
