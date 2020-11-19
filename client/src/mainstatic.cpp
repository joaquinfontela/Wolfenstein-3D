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
        Area destArea2(300, 290, 180, 180);
        gun.render(srcArea2, destArea2); 

        window.render();
        SDL_Delay(5000);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
