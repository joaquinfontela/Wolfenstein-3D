#include "luaraycaster.h"

namespace Lua {

  void Raycaster::run() {

    int iters = 0;

    while(alive){

      iters++;

      double dirX = this->player->dirX;
      double dirY = this->player->dirY;
      double x = this->player->x;
      double y = this->player->y;
      double planeX = this->player->planeX;
      double planeY = this->player->planeY;

      double distanceBuffer[this->width];

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
            if (wasADoor = matrix.isDoor(matrixXCoord, matrixYCoord)) {
              hit = (matrix.getDoorState(matrixXCoord, matrixYCoord) == CLOSED);
            } else if (!wasADoor) {
              hit = 1;
            }
          }
        }

        bool isSide = (side == 0);
        double perpendicularWallDistance = (isSide * (matrixXCoord - x + ((1 - dx) >> 1)) / (rayDirX)) +
                                          (!isSide * (matrixYCoord - y + ((1 - dy) >> 1)) / (rayDirY));

        distanceBuffer[i] = perpendicularWallDistance;
      }

      this->lock.lock();
      for (Drawable* d : this->sprites) { d->loadDistanceWithCoords(x, y); }
      std::vector<Drawable*>::iterator it = this->sprites.begin();
      while (it != this->sprites.end()) {
        // COMPLETAR xd
        ++it;
      }
      this->lock.unlock();

    }
  }

}
