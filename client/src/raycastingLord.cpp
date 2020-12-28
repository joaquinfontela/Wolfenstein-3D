#include <SDL2/SDL.h>
#include <math.h>

#include <exception>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

#include "sdltexture.h"
#include "texturemanager.h"
#include "sdlwindow.h"
#include "drawable.h"

#define EPSILON 0.0001
#define PI 3.14159265359
#define HEIGHT 600
#define WIDTH 800
#define IMG_PATH "../media/"
#define DIMX 12
#define DIMY 12

static void renderWithPerspective(double posX, double posY, double dirX, double dirY, double planeX, double planeY, int matrix[DIMX][DIMY], TextureManager& manager, std::vector<Drawable>& sprites){

  double zBuffer[WIDTH];
  for (int x = 0; x < WIDTH; x++) {
    double cameraX = 2 * x / (double)WIDTH - 1;
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
    if(rayDirY < 0) {
      stepY = -1;
      sideDistY = (posY - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    while (hit == 0) {
      if(sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }

      if(mapX >= DIMX || mapY >= DIMY || mapX < 0 || mapX < 0){
        mapX = INT_MAX;
        mapY = INT_MAX;
      }

      if(matrix[mapX][mapY] > 0) hit = 1;
    }

    if(side == 0) {
      perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    } else {
      perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
    }

    int lineHeight = (int) (HEIGHT/ perpWallDist);
    int offset = 0;

    double wallX;
    if (side == 0) wallX = posY + perpWallDist * rayDirY;
    else wallX = posX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    int texX = int(wallX * double(64));
    if(side == 0 && rayDirX > 0) texX = 64 - texX - 1;
    if(side == 1 && rayDirY < 0) texX = 64 - texX - 1;

    if(side == 0) {
       offset = int(sideDistX) % 64;
    } else {
       offset = int(sideDistY) % 64;
    }

    Area destArea(x, (HEIGHT - lineHeight) / 2, 1, lineHeight);
    Area srcArea(texX, 0, 1, lineHeight);

    manager.render(matrix[mapX][mapY], srcArea, destArea);

    zBuffer[x] = perpWallDist;
  }

  for (Drawable& d : sprites) {
    d.loadDistanceWithCoords(posX, posY);
  }

  std::sort(sprites.begin(), sprites.end());

  for (Drawable& d : sprites) {
    d.draw(manager, posX, posY, dirX, dirY, planeX, planeY, zBuffer);
  }
}

void renderAnimationTest(SdlTexture& gun) {
  int seconds = (int(SDL_GetTicks()) / 1000) % 4;
  Area srcArea(64, 0, 64, 64);
  Area destArea(WIDTH/2 - 130, HEIGHT/2 - 78, 250, 250);
  gun.renderOnTime(seconds, srcArea, destArea);
}
  
int main(int argc, char** argv) {

  int matrix[DIMX][DIMY] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
                            {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int exitcode = 0;
    SdlWindow window(WIDTH, HEIGHT);

    TextureManager manager(&window);
    
    Drawable nazi(6,4,3);
    Drawable barrel1(4,6,6);
    Drawable barrel2(7,7,6);
    Drawable greenlight1(2,5,7);
    Drawable greenlight2(2,7,7);
    std::vector<Drawable> sprites({nazi, barrel1, barrel2, greenlight1, greenlight2});

    double posX = 6, posY = 4;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    double oldDirX = 0;
    double oldPlaneX = 0;
      
    bool leaving = false;
    
    while (!leaving) {
      SDL_Event event;
      window.fillWolfenstein();
      renderWithPerspective(posX, posY, dirX, dirY, planeX, planeY, matrix, manager, sprites);
      //back.renderAll({.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT});
      //renderAnimationTest(gun);
      window.render();

      double moveSpeed = 0.25;
      double rotSpeed = 0.3;

      while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          leaving = true;
          break;
        } else if (event.type == SDL_KEYDOWN) {
          SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
          switch (key.keysym.sym) {
            case SDLK_w:
              if(matrix[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
              if(matrix[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
              break;
            case SDLK_d:
              oldDirX = dirX;
              dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
              dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
              oldPlaneX = planeX;
              planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
              planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
              break;
            case SDLK_a:
              oldDirX = dirX;
              dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
              dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
              oldPlaneX = planeX;
              planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
              planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
              break;
            case SDLK_s:
              if(matrix[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
              if(matrix[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
              break;
            case SDLK_LEFT:
              break;
            case SDLK_RIGHT:
              break;
          }
        }
    }
  }
  return exitcode;
}
