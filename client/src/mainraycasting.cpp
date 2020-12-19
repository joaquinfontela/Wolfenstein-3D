#include <SDL2/SDL.h>
#include <math.h>

#include <climits>
#include <exception>
#include <iostream>

#include "anglemanager.h"
#include "texturemanager.h"
#include "sdltexture.h"
#include "sdlwindow.h"

#define EPSILON 0.0001
#define PI 3.14159265359
#define HEIGHT 600
#define WIDTH 800
#define IMG_PATH "../media/"
#define DIMX 12
#define DIMY 12

static void renderWithPerspective(int x, int y, int viewAngle,
                                  SdlTexture* img1, SdlTexture* img2) {
  int matrix[DIMX][DIMY] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
                            {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  double distanceToProyection = floor((WIDTH / 2) / (tan((PI / 2) - PI / 3)));

  AngleManager angles;

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
  for (int i = 0; i < WIDTH; i++) {
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

        if (xIndex >= DIMX || yIndex >= DIMY || xIndex < 0 || yIndex < 0) {
          distanceTwo = INT_MAX;
          break;
        } else if (matrix[xIndex][yIndex] != 0) {
          secondHit = matrix[xIndex][yIndex];
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

        if (xIndex >= DIMX || yIndex >= DIMY || xIndex < 0 || yIndex < 0) {
          distanceOne = INT_MAX;
          break;
        } else if (matrix[xIndex][yIndex] != 0) {
          firstHit = matrix[xIndex][yIndex];
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
    if (textureToUse == 1){
      img1->render(srcArea, destArea);
    } else {
      img2->render(srcArea, destArea);
    }

    alpha += 1;
    while (alpha >= angles.ANGLE360) alpha -= angles.ANGLE360;
  }
}

int main(int argc, char** argv) {

  int exitcode = 0;
  try {
    SdlWindow window(WIDTH, HEIGHT);
    SdlTexture im1(IMG_PATH "wall.png", window);
    SdlTexture im2(IMG_PATH "wall2.png", window);
    SdlTexture gun(IMG_PATH "chaingun2.png", window);
    SdlTexture back(IMG_PATH "hud.png", window);
  
    TextureManager manager;
    manager.loadTexture(2,&gun);
    manager.loadTexture(3,&back);

    int y = 370;
    int x = 370;
    int deltax = 0;
    int deltay = 0;
    int xmouse = 0;
    AngleManager angles;

    double viewAngle = angles.ANGLE270;
    Area a = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    Area b = {.x = WIDTH/2 - 130, .y = HEIGHT/2 - 78, .w = 250, .h = 250};

    while (true) {
      SDL_Event event;
      window.fillWolfenstein();
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_a:
            if (x + 10 < DIMX * 64) deltax = 10;
            break;
          case SDLK_d:
            if (x - 10 > 0) deltax = -10;
            break;
          case SDLK_w:
            if (y + 10 < DIMY * 64) deltay = 10;
            break;
          case SDLK_s:
            if (y - 10 > 0) deltay = -10;
            break;
          case SDLK_LEFT:
            viewAngle -= angles.ANGLE10;
            if (viewAngle < 0) viewAngle += angles.ANGLE360;
            break;
          case SDLK_RIGHT:
            viewAngle += angles.ANGLE10;
            if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        window.playOrStopAudio();
      } else if (event.type == SDL_MOUSEMOTION) {
        if (event.motion.x > xmouse) {
          viewAngle += angles.ANGLE1p5;
          if (viewAngle > angles.ANGLE360) viewAngle -= angles.ANGLE360;
        } else {
          viewAngle -= angles.ANGLE1p5;
          if (viewAngle < 0) viewAngle += angles.ANGLE360;
        }
        xmouse = event.motion.x;
      }

      double theta = viewAngle - angles.ANGLE270;
      if (theta < 0) theta += angles.ANGLE360;
      if (theta > angles.ANGLE360) theta -= angles.ANGLE360;
      x -= deltax * angles.fCos(theta) - deltay * angles.fSin(theta);
      y -= deltax * angles.fSin(theta) + deltay * angles.fCos(theta);
      deltax = 0;  // Rotation matrix ^^^
      deltay = 0;

      renderWithPerspective(x, y, viewAngle, &im1, &im2);
      manager.renderAll(3,a);
      manager.renderAll(2,b);
      window.render();
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    exitcode = 1;;
  }
  return exitcode;
}
