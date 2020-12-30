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
  if (TTF_Init() < 0) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  this->font = TTF_OpenFont(FONT_PATH "wolfenstein.ttf", 25);
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface* surface = TTF_RenderText_Solid(this->font, "jaja salu2", color);
  this->text = new SdlTexture(surface, window);
  SDL_FreeSurface(surface);
}

void Hud::renderText() {
  text->renderAll({.x = 100, .y = 100, .h = 200, .w = 200});
}

Hud::~Hud() {
  delete this->text;
  SDL_DestroyTexture(texture);
  TTF_CloseFont(this->font);
  TTF_Quit();
}
