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
#define GREY {169, 168, 244}

Hud::Hud(SdlWindow* window, Player* player) :
  window(window), renderer(window->getRenderer()), texture(nullptr), player(player) {
  if (TTF_Init() < 0 || !(this->font = TTF_OpenFont(FONT_PATH "wolfenstein.ttf", 100))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
}

void Hud::renderLifes() {
  int x, y;
  this->window->getWindowSize(&x, &y);
  int width = x / 30;
  int height = y / 6;
  x -= width + 620 * x / 1000;
  y -= height - y / 200;
  SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height};
  this->renderText(std::to_string(player->lives).c_str(), &rect);
}

void Hud::renderFps(int fps) {
  int x, y;
  this->window->getWindowSize(&x, &y);
  int width = x / 16;
  int height = y / 6;
  x -= width + 893 * x / 1000;
  if (fps < 100){
    width -= 5;
    x += 5;
  }
  y -= height - y / 275;
  SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height};
  this->renderText(std::to_string(fps).c_str(), &rect);
}

void Hud::renderHealth() {
  int x, y;
  this->window->getWindowSize(&x, &y);
  int width = x / 16;
  int height = y / 6;
  x -= width + 405 * x / 1000;
  if (player->health < 100){
    width -= 5;
    x += 5;
  }
  y -= height - y / 275;
  SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height};
  this->renderText(std::to_string(player->health).c_str(), &rect);
}

void Hud::renderText(const char* text, SDL_Rect* rect) {
  SDL_Color color = GREY;
  SDL_Surface* surface = NULL;
  if (!(surface = TTF_RenderText_Solid(this->font, text, color))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  if (!(this->texture = SDL_CreateTextureFromSurface(this->renderer, surface))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  SDL_RenderCopy(this->renderer, this->texture, NULL, rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(this->texture);
}

Hud::~Hud() {
  //delete this->text;
  SDL_DestroyTexture(texture);
  TTF_CloseFont(this->font);
  TTF_Quit();
}
