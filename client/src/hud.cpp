#include "hud.h"
#include "player.h"
#include "sdlexception.h"
#include "sdltexture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define TTF_INIT_ERROR "\nError on initialization: "
#define FONT_PATH "../media/"
#define SIZE 25

Hud::Hud(SdlWindow* window, Player*) : window(window), player(player) {
  if (TTF_Init() < 0 || !(this->font = TTF_OpenFont(FONT_PATH "wolfenstein.ttf", 100))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface* surface = NULL;
  if (!(surface = TTF_RenderText_Solid(this->font, "jaja salu2", color))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  this->text = new SdlTexture(surface, *window);
  //SDL_FreeSurface(surface);
}

void Hud::renderText() {
  Area srcArea(0,0,200,200);
  Area destArea(100,100,200,200);
  SDL_ClearError();
  std::cout << "SAMALE-CUM" << std::endl;
  std::cout << "Drawing exit code: " << text->render(srcArea, destArea)
  << " and error code: " << SDL_GetError() << std::endl;
}

Hud::~Hud() {
  delete this->text;
  SDL_DestroyTexture(texture);
  TTF_CloseFont(this->font);
  TTF_Quit();
}
