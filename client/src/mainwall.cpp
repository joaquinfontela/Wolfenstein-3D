#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "sdlwindow.h"
#include "sdltexture.h"

#define TEMP_HEIGHT 600
#define TEMP_WIDTH 800
#define IMG_PATH "../media/"

int main(int argc, char** argv){

  try {
    SdlWindow window(TEMP_WIDTH, TEMP_HEIGHT);
    SdlTexture im(IMG_PATH "bluesquare.jpg", window);

    Area srcArea(0, 0, TEMP_HEIGHT, TEMP_WIDTH);

    int w = 100; int h = 100;
    int x = TEMP_WIDTH/2;
    int y = TEMP_HEIGHT/2;
    while (true){
      SDL_Event event;
      Area destArea(x, y, w, h);
      window.fill();
      im.render(srcArea, destArea); 
      window.render();
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        break;
      } else if (event.type == SDL_KEYDOWN) {
        std::cout << "X: " << x << " Y: " << y << " W: " << w << " H: " << h << std::endl;
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&) event;
        switch (key.keysym.sym) {
          case SDLK_LEFT:
            std::cout << " izq " << std::endl;
            x += 10; 
            break; 
          case SDLK_RIGHT:
            std::cout << " der " << std::endl;
            x -= 10;
            break; 
          case SDLK_UP:
            std::cout << " arriba" << std::endl;
            w += 10;
            h += 10;
            x -= 5;
            y -= 5; 
            break; 
          case SDLK_DOWN:
            std::cout << " bajo " << std::endl;
            w -= 10;
            h -= 10;
            x += 5;
            y += 5; 
            break;
        }
      }
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
