#include <SDL2/SDL.h>

#include <exception>
#include <iostream>

#include "sdldrawing.h"
#include "sdltexture.h"
#include "sdlwindow.h"

#define HEIGHT 600
#define WIDTH 800
#define IMG_PATH "../media/"

int main(int argc, char** argv) {

  try {
    SdlWindow window(WIDTH, HEIGHT);
    window.fill();

    Area newDestArea(0, 0, 100, 100);
    Drawing gun(IMG_PATH "chaingun1.jpg", window, newDestArea);
    gun.draw();
    window.render();

    while (true) {
      SDL_Event event;
      window.fill();
      gun.draw();
      window.render();
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&)event;
        switch (key.keysym.sym) {
          case SDLK_LEFT:
            std::cout << " izq " << std::endl;
            gun.moveLeft(10);
            break;
          case SDLK_RIGHT:
            std::cout << " der " << std::endl;
            gun.moveRight(10);
            break;
          case SDLK_UP:
            std::cout << " arriba" << std::endl;
            gun.moveUp(10);
            break;
          case SDLK_DOWN:
            std::cout << " bajo " << std::endl;
            gun.moveDown(10);
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          std::cout << " mouse izq " << std::endl;
          gun.makeSmaller(10);
        } else {  // Fix later, no necesariamente un click del mouse es izq o
                  // der.
          std::cout << " mouse der" << std::endl;
          gun.makeBigger(10);
        }
      }
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
