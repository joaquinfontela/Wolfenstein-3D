#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "sdlwindow.h"
#include "sdltexture.h"

#define TEMP_HEIGHT 800
#define TEMP_WIDTH 600
#define IMG_PATH "../media/"

int main(int argc, char** argv){
  try {
    SdlWindow window(TEMP_HEIGHT, TEMP_WIDTH);
    window.fill();
    SdlTexture im(IMG_PATH "hud.jpg", window);
    SdlTexture gun(IMG_PATH "chaingun1.jpg", window);

    Area srcArea(0, 0, TEMP_HEIGHT, TEMP_WIDTH);
    Area destArea(0, 0, TEMP_HEIGHT, TEMP_WIDTH);
    im.render(srcArea, destArea); 
    window.render();

    Area srcArea2(0, 0, 100, 100);
    Area destArea3(300, 290, 180, 180);
    gun.render(srcArea2, destArea3); 

    window.render();

    int x = 300; int y = 290;
    int a = 180; int b = 180;
    bool alive = true;
    while (alive){
      SDL_Event event;
      Area destArea2(x, y, a, b);
      im.render(srcArea, destArea); 
      gun.render(srcArea2, destArea2); 
      window.render();
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT) {
        alive = false;
      } else if (event.type == SDL_KEYDOWN) {
        std::cout << "X: " << x << " Y: " << y;
        SDL_KeyboardEvent& key = (SDL_KeyboardEvent&) event;
        switch (key.keysym.sym) {
          case SDLK_LEFT:
            std::cout << " izq " << std::endl;
            x -= 10; 
            break; 
          case SDLK_RIGHT:
            std::cout << " der " << std::endl;
            x += 10; 
            break; 
          case SDLK_UP:
            std::cout << " arriba" << std::endl;
            y -= 10;
            break; 
          case SDLK_DOWN:
            std::cout << " bajo " << std::endl;
            y += 10; 
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT){
            std::cout << " mouse izq " << std::endl;
            a -= 10;
            b -= 10;
        } else { // Fix later, no necesariamente un click del mouse es izq o der.
            std::cout << " mouse der" << std::endl;
            a += 10;
            b += 10;
        }
      }
    }

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
