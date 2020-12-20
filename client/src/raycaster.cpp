#include <SDL2/SDL.h>
#include <math.h>

#include <climits>
#include <exception>
#include <iostream>

#include "anglemanager.h"
#include "texturemanager.h"
#include "sdltexture.h"
#include "sdlwindow.h"
#include "raycaster.h"

#define EPSILON 0.0001
#define PI 3.14159265359
#define IMG_PATH "../media/"

void Raycaster::run() {
  while (alive) {  
    int x = this->self->getX();
    int y = this->self->getY();
    int viewAngle = this->self->getAngle();

    double xBoxIntersection, yBoxIntersection;
    double dv, dh, dx, dy;
    double distanceOne = 0;
    double distanceTwo = 0;

    int xGrid, yGrid;
    int xIndex, yIndex;
    int alpha = viewAngle - angles.ANGLE30;

    if (alpha < 0) {
      alpha += angles.ANGLE360;
    }

    int firstHit, secondHit;
    for (int i = 0; i < this->width; i++) {
      std::cout << "Casting ray at angle: " << (alpha * 60) / WIDTH
                << " in column: " << i << std::endl;

      if (alpha > angles.ANGLE0 && alpha < angles.ANGLE180) {
        yGrid = floor(y / 64) * 64 + 64;
        dh = 64;
        xBoxIntersection = angles.fITanTable[alpha] * (yGrid - y) + x;
      } else {
        yGrid = floor(y / 64) * 64 - 1;
        dh = -64;
        xBoxIntersection = angles.fITanTable[alpha] * (yGrid - y) + x;
      }

      if (alpha == angles.ANGLE0 || alpha == angles.ANGLE180) {
        distanceTwo = INT_MAX;
      } else {
        dx = angles.fXStepTable[alpha];
        while (true) {
          xIndex = floor(xBoxIntersection / 64);
          yIndex = floor(yGrid / 64);

          if (xIndex >= matrix.dimx || yIndex >= matrix.dimy || xIndex < 0 || yIndex < 0) {
            distanceTwo = INT_MAX;
            break;
          } else if (matrix.matrix[xIndex][yIndex] != 0) {
            secondHit = matrix.matrix[xIndex][yIndex];
            distanceTwo =
                abs(xBoxIntersection - x) * abs(angles.fICosTable[alpha]);
            break;
          } else {
            xBoxIntersection += dx;
            yGrid += dh;
          }
        }
      }

      if (alpha < angles.ANGLE90 || alpha > angles.ANGLE270) {
        xGrid = floor(x / 64) * 64 + 64;
        dv = 64;
        yBoxIntersection = angles.fTanTable[alpha] * (xGrid - x) + y;
      } else {
        xGrid = floor(x / 64) * 64 - 1;
        dv = -64;
        yBoxIntersection = angles.fTanTable[alpha] * (xGrid - x) + y;
      }
      if (alpha == angles.ANGLE90 || alpha == angles.ANGLE270) {
        distanceOne = INT_MAX;
      } else {
        dy = angles.fYStepTable[alpha];
        while (true) {
          xIndex = floor(xGrid / 64);
          yIndex = floor(yBoxIntersection / 64);

          if (xIndex >= matrix.dimx || yIndex >= matrix.dimy || xIndex < 0 || yIndex < 0) {
            distanceOne = INT_MAX;
            break;
          } else if (matrix.matrix[xIndex][yIndex] != 0) {
            firstHit = matrix.matrix[xIndex][yIndex];
            distanceOne =
                abs(yBoxIntersection - y) * abs(angles.fISinTable[alpha]);
            break;
          } else {
            yBoxIntersection += dy;
            xGrid += dv;
          }
        }
      }

      double distanceToWall =
          (distanceOne > distanceTwo) ? distanceTwo : distanceOne;

      double wallHeight = (64.0 / distanceToWall) * distanceToProyection;
      wallHeight *= angles.fFishTable[i];

      int offset;
      int textureToUse;
      if (distanceOne > distanceTwo) {
        textureToUse = secondHit;
        distanceToWall = distanceTwo;
        offset = (int)xBoxIntersection % 64;
      } else {
        textureToUse = firstHit;
        distanceToWall = distanceOne;
        offset = (int)yBoxIntersection % 64;
      }

      int height = ceil(wallHeight);
      Area srcArea(offset, 0, 1, height);
      Area destArea(i, (HEIGHT - height) / 2, 1, height);
      std::cout << "tengo que renderizar." << std::endl;
      this->manager.render(textureToUse, srcArea, destArea);
      alpha += 1;
      while (alpha >= angles.ANGLE360) alpha -= angles.ANGLE360;
    }    
  }
}

