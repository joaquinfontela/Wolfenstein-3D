#include "../includes/raycaster.h"

#include <math.h>
#include <time.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#include "../includes/clientprotocol.h"
#include "../includes/door.h"
#include "../includes/doortimer.h"
#include "../includes/drawable.h"

bool Raycaster::hitDoor(const int& matrixXCoord, const int& matrixYCoord) {
  for (Door& d : doors) {
    if (d.matrixXCoord == matrixXCoord && d.matrixYCoord == matrixYCoord) {
      return true;
    }
  }
  return false;
}

void Raycaster::sleep(float diff) {
  if (diff < 16.6) {
    std::chrono::duration<double, std::milli> delta(16.6 - diff);
    auto deltaMs = std::chrono::duration_cast<std::chrono::milliseconds>(delta);
    std::this_thread::sleep_for(std::chrono::milliseconds(deltaMs.count()));
  }
}

void Raycaster::getPlayerData() {
  this->dirX = this->player->dirX;
  this->dirY = this->player->dirY;
  this->x = this->player->x;
  this->y = this->player->y;
  this->planeX = this->player->planeX;
  this->planeY = this->player->planeY;
}

void Raycaster::DDA(int& side, int& texNum, int& i, int& dx, int& dy, int& matrixXCoord,
        int& matrixYCoord, double& sideDistX, double& sideDistY, double& deltaDistanceX,
        double& deltaDistanceY, double& cameraXCoord) {

  bool wasADoor;
  int hit = 0;
  while (!hit) {
    bool isSideDistXgreaterToY = (sideDistX < sideDistY);
    sideDistX += deltaDistanceX * isSideDistXgreaterToY;
    sideDistY += deltaDistanceY * !isSideDistXgreaterToY;
    matrixXCoord += dx * isSideDistXgreaterToY;
    matrixYCoord += dy * !isSideDistXgreaterToY;
    side = !isSideDistXgreaterToY;

    if (matrixXCoord >= matrix.dimx || matrixYCoord >= matrix.dimy ||
        matrixXCoord < 0 || matrixYCoord < 0) {
      matrixXCoord = INT_MAX;
      matrixYCoord = INT_MAX;
      hit = 1;
    } else if ((texNum = matrix.get(matrixXCoord, matrixYCoord)) > 0) {
      if ((wasADoor = matrix.isDoor(matrixXCoord, matrixYCoord)) &&
          (!(this->doors.size()) ||
           !this->hitDoor(matrixXCoord, matrixYCoord))) {
        Door door(matrixXCoord, matrixYCoord, this->width, this->height, dx,
                  dy, side, cameraXCoord, i, &matrix);
        this->doors.push_back(door);
        hit = (matrix.getDoorState(matrixXCoord, matrixYCoord) == CLOSED);
      } else if (!wasADoor) {
        hit = 1;
      }
    }
  }
}

void Raycaster::drawDoors(double* distanceBuffer) {
  // It is not necessary to sort the doors (depending on their distance to
  // the player) because they are already pushed in the vector as you detect
  // them, meaning that the doors are already sorted. Thanks LIFO.
  while (!this->doors.empty()) {
    Door& d = this->doors.back();
    d.draw(manager, x, y, dirX, dirY, planeX, planeY, distanceBuffer);
    this->doors.pop_back();
  }
}

void Raycaster::drawWalls(int& side, int& texNum, int& i, int& dx, int& dy,
             double* distanceBuffer, int& matrixXCoord, int& matrixYCoord,
             double rayDirX, double rayDirY) {
  bool isSide = (side == 0);
  double perpendicularWallDistance =
      (isSide * (matrixXCoord - x + ((1 - dx) >> 1)) / (rayDirX)) +
      (!isSide * (matrixYCoord - y + ((1 - dy) >> 1)) / (rayDirY));

  int wallHeight = int(this->height / perpendicularWallDistance);

  double wallX = (isSide * (y + perpendicularWallDistance * rayDirY)) +
                 (!isSide * (x + perpendicularWallDistance * rayDirX));
  wallX -= floor((wallX));

  int stripe = int(wallX * double(BLOCKSIZE));
  bool condition = ((isSide && rayDirX > 0) || (!isSide && rayDirY < 0));
  stripe = (BLOCKSIZE - stripe - 1) * condition + stripe * (!condition);

  bool tooFar = (wallHeight < BLOCKSIZE);
  srcArea.update(stripe, 0, 1, tooFar * BLOCKSIZE + !tooFar * wallHeight);
  destArea.update(i, (this->height - wallHeight) >> 1, 1, wallHeight);
  this->manager.render(texNum, srcArea, destArea);
  distanceBuffer[i] = perpendicularWallDistance;
}

void Raycaster::rayCastGame(double* distanceBuffer) {
  for (int i = 0; i < this->width; i++) {
    double cameraXCoord = (i << 1) / (double)this->width - 1;
    double rayDirX = dirX + planeX * cameraXCoord;
    double rayDirY = dirY + planeY * cameraXCoord;

    int matrixXCoord = int(x);
    int matrixYCoord = int(y);

    double sideDistX, sideDistY;

    double deltaDistanceX = std::abs(1 / rayDirX);
    double deltaDistanceY = std::abs(1 / rayDirY);

    int side, texNum = 1, dx = 1, dy = 1;
    bool isRayDirXNegative = (rayDirX < 0);
    bool isRayDirYNegative = (rayDirY < 0);
    dx -= (isRayDirXNegative << 1);  // Swicthing signs.
    sideDistX =
        (isRayDirXNegative * (x - matrixXCoord) * deltaDistanceX) +
        (!isRayDirXNegative * (matrixXCoord + 1.0 - x) * deltaDistanceX);
    dy -= (isRayDirYNegative << 1);  // Swicthing signs.
    sideDistY =
        (isRayDirYNegative * (y - matrixYCoord) * deltaDistanceY) +
        (!isRayDirYNegative * (matrixYCoord + 1.0 - y) * deltaDistanceY);

    this->DDA(side, texNum, i, dx, dy, matrixXCoord, matrixYCoord, sideDistX,
              sideDistY, deltaDistanceX, deltaDistanceY, cameraXCoord);
    this->drawWalls(side, texNum, i, dx, dy, distanceBuffer, matrixXCoord,
                    matrixYCoord, rayDirX, rayDirY);
    this->drawDoors(distanceBuffer);
  }
}

void Raycaster::run() {
  this->startingscreen.draw();
  auto t1 = std::chrono::steady_clock::now();
  auto drawableTime1 = std::chrono::steady_clock::now();
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  DoorTimer timer(this->matrix, this->alive);
  timer.start();
  int iters = 0;
  while (alive) {

    start = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> timePerFrame = start - end;
    this->sleep(timePerFrame.count());
    end = std::chrono::system_clock::now();

    iters++;
    this->manager.drawBackground();

    this->getPlayerData();
    double distanceBuffer[this->width];

    float totalTime = 0;

    this->rayCastGame(distanceBuffer);

    auto drawableTime2 = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> drawableDiff =
        drawableTime2 - drawableTime1;

    this->sprites.raycastSprites(x, y, dirX, dirY, planeX, planeY,
                                 distanceBuffer, drawableDiff.count(), manager);

    drawableTime1 = drawableTime2;

    auto t2 = std::chrono::steady_clock::now();
    totalTime +=
        (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1))
            .count();
    if (totalTime > 1000) {
      totalTime = 0;
      std::chrono::duration<float, std::milli> diff = t2 - t1;
      this->hud.updateFpsCounter((iters * 1000) / ceil(diff.count()));
      t1 = t2;
      iters = 0;
      this->hud.updateBjFace();
    }

    this->hud.update();
    this->manager.updateScreen();
  }

  timer.join();
}
