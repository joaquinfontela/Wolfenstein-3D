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
#define FACES_PER_IMG 3

void Hud::update(int fps) {
  this->renderFps(fps);
  this->renderLifes();
  this->renderHealth();
  this->renderFace();
}

void Hud::renderFace() {
  int health = this->player->health;
  int x, y;
  this->window->getWindowSize(&x, &y);
  int width, height, id;
  if (health > 66) {
    id = 13;
  } else if (health > 33) {
    id = 14;
  } else {
    id = 15;
  }
  this->manager.getTextureSizeWithId(id, &width, &height);
  this->bjface->setSlideWidth(&width);
  Area destArea(x - ((x * 93)/ 160.0), y - ((y * 97) / 600.0),
                7 * x / 80, 2 * y / 15);
  this->bjface->renderActualFrame(destArea, id);
}

void Hud::updateBjFace() {
  this->bjface->updateFrame();
}

Hud::Hud(SdlWindow* window, Player* player, TextureManager& manager) :
  window(window), renderer(window->getRenderer()), texture(nullptr), player(player), manager(manager) {
  if (TTF_Init() < 0 || !(this->font = TTF_OpenFont(FONT_PATH "wolfenstein.ttf", 100))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  this->bjface = new SdlAnimation(manager, FACES_PER_IMG);
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
  x += x / 11;
  if (fps < 100){
    width -= width / 160;
    x += x / 50;
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
  x -= width + 49 * x / 125;
  if (player->health < 100){
    width -= width / 160;
    x += x / 53;
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
  delete this->bjface;
  SDL_DestroyTexture(texture);
  TTF_CloseFont(this->font);
  TTF_Quit();
}
