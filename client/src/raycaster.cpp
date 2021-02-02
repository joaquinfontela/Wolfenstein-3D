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

bool Raycaster::hitDoor(const int& matrixXCoord, const int& matrixYCoord) {
  for (Door& d : doors) {
    if (d.matrixXCoord == matrixXCoord && d.matrixYCoord == matrixYCoord) {
      return true;
    }
  }
  return false;
}

void Raycaster::run(){

  auto t1 = std::chrono::steady_clock::now();
  auto drawableTime1 = std::chrono::steady_clock::now();
  DoorTimer timer(this->matrix, this->alive);
  timer.start();
  int iters = 0;

  while(alive){
    iters++;
    this->window->fillWolfenstein();

    double dirX = this->player->dirX;
    double dirY = this->player->dirY;
    double x = this->player->x;
    double y = this->player->y;
    double planeX = this->player->planeX;
    double planeY = this->player->planeY;

    double distanceBuffer[this->width];
    float totalTime = 0;

    int adjustment = this->width * 3 / 200;
    for(int i = adjustment; i < this->width - adjustment; i++) {

      double cameraXCoord = (i << 1) / (double)this->width - 1;
      double rayDirX = dirX + planeX * cameraXCoord;
      double rayDirY = dirY + planeY * cameraXCoord;

      int matrixXCoord = int(x);
      int matrixYCoord = int(y);

      double sideDistX, sideDistY;

      double deltaDistanceX = std::abs(1 / rayDirX);
      double deltaDistanceY = std::abs(1 / rayDirY);

      int dx = 1, dy = 1, hit = 0, texNum = 1, side;
      bool wasADoor;

      bool isRayDirXNegative = (rayDirX < 0);
      bool isRayDirYNegative = (rayDirY < 0);
      dx -= (isRayDirXNegative << 1); // Swicthing signs.
      sideDistX = (isRayDirXNegative * (x - matrixXCoord) * deltaDistanceX) +
                  (!isRayDirXNegative * (matrixXCoord + 1.0 - x) * deltaDistanceX);
      dy -= (isRayDirYNegative << 1); // Swicthing signs.
      sideDistY = (isRayDirYNegative * (y - matrixYCoord) * deltaDistanceY) +
                  (!isRayDirYNegative * (matrixYCoord + 1.0 - y) * deltaDistanceY);

      while (!hit) {
        bool isSideDistXgreaterToY = (sideDistX < sideDistY);
        sideDistX += deltaDistanceX * isSideDistXgreaterToY;
        sideDistY += deltaDistanceY * !isSideDistXgreaterToY;
        matrixXCoord += dx * isSideDistXgreaterToY;
        matrixYCoord += dy * !isSideDistXgreaterToY;
        side = !isSideDistXgreaterToY;

        if (matrixXCoord >= matrix.dimx || matrixYCoord >= matrix.dimy || matrixXCoord < 0 || matrixYCoord < 0) {
          matrixXCoord = INT_MAX;
          matrixYCoord = INT_MAX;
          hit = 1;
        } else if ((texNum = matrix.get(matrixXCoord, matrixYCoord)) > 0) {
          if ((wasADoor = matrix.isDoor(matrixXCoord, matrixYCoord)) && (!(this->doors.size()) || !this->hitDoor(matrixXCoord,matrixYCoord))) {
            Door door(matrixXCoord, matrixYCoord, this->width, this->height, dx, dy, side, cameraXCoord, i, &matrix);
            this->doors.push_back(door);
            hit = (matrix.getDoorState(matrixXCoord, matrixYCoord) == CLOSED);
          } else if (!wasADoor) {
            hit = 1;
          }
        }
      }

      bool isSide = (side == 0);
      double perpendicularWallDistance = (isSide * (matrixXCoord - x + ((1 - dx) >> 1)) / (rayDirX)) +
                            (!isSide * (matrixYCoord - y + ((1 - dy) >> 1)) / (rayDirY));

      int wallHeight = int(this->height/ perpendicularWallDistance);

      double wallX = (isSide * (y + perpendicularWallDistance * rayDirY)) +
                     (!isSide * (x + perpendicularWallDistance * rayDirX));
      wallX -= floor((wallX));

      int doorStripe = int(wallX * double(BLOCKSIZE));
      bool condition = ((isSide && rayDirX > 0) || (!isSide && rayDirY < 0));
      doorStripe = (BLOCKSIZE - doorStripe - 1) * condition + doorStripe * (!condition);

      bool tooFar = (wallHeight < BLOCKSIZE);
      srcArea.update(doorStripe, 0, 1, tooFar * BLOCKSIZE + !tooFar * wallHeight);
      destArea.update(i, (this->height - wallHeight) >> 1, 1, wallHeight);
      this->manager.render(texNum, srcArea, destArea);
      distanceBuffer[i] = perpendicularWallDistance;

      // It is not necessary to sort the doors (depending on their distance to the player)
      // because they are already pushed in the vector as you detect them, meaning that
      // the doors are already sorted. Thanks LIFO.
      while(!this->doors.empty()){
        Door& d = this->doors.back();
        d.draw(manager, x, y, dirX, dirY, planeX, planeY, distanceBuffer);
        this->doors.pop_back();
      }

    }

    auto drawableTime2 = std::chrono::steady_clock::now();

    this->lock.lock();
    for (Drawable* d : this->sprites) { d->loadDistanceWithCoords(x, y); }
    std::sort(this->sprites.begin(), this->sprites.end(), []
      (Drawable* a, Drawable* b) -> bool { return *a < *b; });

    std::vector<Drawable*>::iterator it = this->sprites.begin();
    std::chrono::duration<float, std::milli> drawableDiff = drawableTime2 - drawableTime1;

    while (it != this->sprites.end()) {
      if (!(*it)->hasToBeDeleted) {
        (*it)->draw(manager, x, y, dirX, dirY, planeX, planeY, distanceBuffer, drawableDiff.count());
        ++it;
      } else {
        delete (*it);
        this->sprites.erase(it);
      }
    }

    this->lock.unlock();

    drawableTime1 = drawableTime2;

    auto t2 = std::chrono::steady_clock::now();
    totalTime += (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)).count();
    if (totalTime > 1000) {
      totalTime = 0;
      std::chrono::duration<float,std::milli> diff = t2 - t1;
      this->hud.updateFpsCounter((iters * 1000)/ceil(diff.count()));
      t1 = t2;
      iters = 0;
      this->hud.updateBjFace();
    }

    this->hud.update();
    this->window->render();
  }

  timer.join();
  this->scoreboard.draw();
}
