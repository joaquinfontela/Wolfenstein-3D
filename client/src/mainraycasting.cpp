#include <SDL2/SDL.h>
#include <math.h>

#include <climits>
#include <exception>
#include <iostream>

#include "anglemanager.h"
#include "texturemanager.h"
#include "sdltexture.h"
#include "raycaster.h"
#include "sdlwindow.h"
#include "../../common/includes/Map/Map.h"

#define EPSILON 0.0001
#define PI 3.14159265359
#define HEIGHT 600
#define WIDTH 800
#define IMG_PATH "../media/"
#define DIMX 12
#define DIMY 12

int main(int argc, char** argv) {

  int exitcode = 0;
  try {
    SdlWindow window(WIDTH, HEIGHT);
    SdlTexture im1(IMG_PATH "wall.png", window);
    SdlTexture im2(IMG_PATH "wall2.png", window);
    SdlTexture im3(IMG_PATH "wall3.png", window);
    SdlTexture im4(IMG_PATH "wall4.png", window);
    SdlTexture gun(IMG_PATH "chaingun2.png", window);
    SdlTexture back(IMG_PATH "hud.png", window);
  
    TextureManager manager;
    manager.loadTexture(1,&im1);
    manager.loadTexture(2,&im2);
    manager.loadTexture(3,&im3);
    manager.loadTexture(4,&im4);
    manager.loadTexture(5,&gun);
    manager.loadTexture(6,&back);
    Map matrix("COMPLETAR CON EL YAML LATER");
    Raycaster caster(WIDTH, HEIGHT, manager, matrix);

    int y = 370;
    int x = 370;
    int deltax = 0;
    int deltay = 0;
    int xmouse = 0;
    AngleManager angles;

    double viewAngle = angles.ANGLE270;
    Area a = {.x = WIDTH/2 - 130, .y = HEIGHT/2 - 78, .w = 250, .h = 250};
    Area b = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};

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

      caster.renderWithPerspective(x, y, viewAngle);
      manager.renderAll(5,a);
      manager.renderAll(6,b);
      window.render();
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    exitcode = 1;;
  }
  return exitcode;
}
