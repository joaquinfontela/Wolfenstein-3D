#include "raycaster.h"
#include "drawable.h"
#include "doortimer.h"
#include "door.h"
#include "clientprotocol.h"
#include <climits>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
#include <time.h>

void Raycaster::drawDoors() {
  /*for (auto d : doors) {
    d->draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer);
  }*/
}

bool Raycaster::hitDoor(const int& mapX, const int& mapY) {
  for (Door& d : doors) {
    if (d.mapX == mapX && d.mapY == mapY) {
      return true;
    }
  }
  return false;
}

void Raycaster::run(){

  auto t1 = std::chrono::steady_clock::now();
  DoorTimer timer(this->matrix, this->alive);
  timer.start();
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

    for(int x = 0; x < this->width; x++) {

      double cameraX = (x << 1) / (double)this->width - 1;
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

      int mapX = int(posX);
      int mapY = int(posY);

      double sideDistX, sideDistY;

      double deltaDistX = std::abs(1 / rayDirX);
      double deltaDistY = std::abs(1 / rayDirY);

      int stepX = 1;
      int stepY = 1;

      int hit = 0;
      int texNum = 1;
      bool wasADoor;
      int side;

      bool isRayDirXNegative = (rayDirX < 0);
      bool isRayDirYNegative = (rayDirY < 0);
      stepX -= (isRayDirXNegative << 1); // Swicthing signs.
      sideDistX = (isRayDirXNegative * (posX - mapX) * deltaDistX) +
                  (!isRayDirXNegative * (mapX + 1.0 - posX) * deltaDistX);
      stepY -= (isRayDirYNegative << 1); // Swicthing signs.
      sideDistY = (isRayDirYNegative * (posY - mapY) * deltaDistY) +
                  (!isRayDirYNegative * (mapY + 1.0 - posY) * deltaDistY);

      while (hit == 0) {
        bool isSideDistXgreaterToY = (sideDistX < sideDistY);
        sideDistX += deltaDistX * isSideDistXgreaterToY;
        sideDistY += deltaDistY * !isSideDistXgreaterToY;
        mapX += stepX * isSideDistXgreaterToY;
        mapY += stepY * !isSideDistXgreaterToY;
        side = !isSideDistXgreaterToY;

        if (mapX >= matrix.dimx || mapY >= matrix.dimy || mapX < 0 || mapY < 0) {
          mapX = INT_MAX;
          mapY = INT_MAX;
          hit = 1;
        } else if ((texNum = matrix.get(mapX, mapY)) > 0) {
          if ((wasADoor = matrix.isDoor(mapX, mapY)) && (!(this->doors.size()) || !this->hitDoor(mapX,mapY))) {
            Door door(mapX, mapY, this->width, this->height, stepX, stepY, side, cameraX, x, &matrix);
            this->doors.push_back(door);
            hit = (matrix.getDoorState(mapX, mapY) == CLOSED);
          } else if (!wasADoor) {
            hit = 1;
          }
        }
      }

      bool isSide = (side == 0);
      double perpWallDist = (isSide * (mapX - posX + ((1 - stepX) >> 1)) / (rayDirX)) +
                            (!isSide * (mapY - posY + ((1 - stepY) >> 1)) / (rayDirY));

      int lineHeight = int(this->height/ perpWallDist);

      double wallX = (isSide * (posY + perpWallDist * rayDirY)) +
                     (!isSide * (posX + perpWallDist * rayDirX));
      wallX -= floor((wallX));

      int texX = int(wallX * double(BLOCKSIZE));
      bool condition = ((isSide && rayDirX > 0) || (!isSide && rayDirY < 0));
      texX = (BLOCKSIZE - texX - 1) * condition + texX * (!condition);

      srcArea.update(texX, 0, 1, (lineHeight < BLOCKSIZE) ? BLOCKSIZE : lineHeight);
      destArea.update(x, (this->height - lineHeight) >> 1, 1, lineHeight);
      this->manager.render(texNum, srcArea, destArea);
      zBuffer[x] = perpWallDist;

      while(!this->doors.empty()){
        // It is not necessary to sort the doors (depending on their distance to the player)
        // because they are already pushed in the vector as you detect them, meaning that
        // the doors are already sorted. Thanks LIFO.
        Door d = this->doors.back();
        this->doors.pop_back();
        d.draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer);
      }

    }

    this->lock.lock();
    for (Drawable* d : this->sprites) { d->loadDistanceWithCoords(posX, posY); }
    std::sort(this->sprites.begin(), this->sprites.end(), []
      (Drawable* a, Drawable* b) -> bool { return *a < *b; });

    for (Drawable* d : this->sprites) { d->draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer); }
    this->lock.unlock();

    #ifdef FPS_FREQ
    #define FPS_FREQ 50
    //Use this with a VM only case.

    if (!(iters % FPS_FREQ)) {
      auto t2 = std::chrono::steady_clock::now();
      std::chrono::duration<float,std::milli> diff = t2 - t1;
      if (!iters) this->hud.updateFpsCounter((1000)/ceil(diff.count()));
      else this->hud.updateFpsCounter((FPS_FREQ * 1000)/ceil(diff.count()));
      t1 = t2;
      this->hud.updateBjFace();
    }

    #endif

    this->hud.update();
    this->window->render();
    iters++;
  }

  timer.join();
}
