#include "hud.h"
#include "player.h"
#include "sdlexception.h"
#include "sdltexture.h"
#include "clientprotocol.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define TTF_INIT_ERROR "\nError on initialization: "
#define SIZE 25
#define FACES_PER_IMG 3
#define GUNS_IN_HUD 5
#define FRAMES_PER_GUN_ANIMATION 20
#define GUN_SLICES FRAMES_PER_GUN_ANIMATION/4

void Hud::update() {
  this->renderFpsCounter();
  this->renderLifes();
  this->renderHealth();
  this->renderFace();
  this->renderTypeOfGun();
  this->renderGun();
  this->framesAlreadyPlayed++;
}

void Hud::renderTypeOfGun() {
  int weaponId = this->player->weaponId;
  this->hudgun->updateFrame(weaponId-1);
  int x, y, width, height;
  this->window->getWindowSize(&x, &y);
  this->manager.getTextureSizeWithId(HUDGUNS, &width, &height);
  this->hudgun->setSlideWidth(&width);
  float aspectRatio = float(height) / float(width);
  width = (x * 9)/50;
  height = width * aspectRatio;
  Area destArea((63 * x) / 80, y - (14 * y) / 80, width , height);
  //std::cout << "id: " << weaponId << " x: " << destArea.getX() << ", y:  " << destArea.getY() << ", w: " << destArea.getWidth() << ", h: " << destArea.getHeight() << " " << std::endl;
  this->hudgun->renderActualFrame(destArea, HUDGUNS);
}

/*
 * Let us call X(T) = Frames rendered in T seconds => FPS = X(T)/T [1/s]
 * And let's say that the number of frames that our animation has is Z.
 * If our animation lasted N frames and we wanted to play it in one second,
 * then we would have to update the frames every FPS/Z number of iterations.
 * Now, if we had N frames that would have to be played in T' seconds, every
 * frame of the animation would have to be updated every (FPS * T')/Z iterations.
 */

void Hud::renderGun() {
  int weaponId = this->player->weaponId;
  if (this->player->isShooting() && !(this->framesAlreadyPlayed % (this->fps / 16))) {
    animationStatus++;
    std::cout << "Shooting with id: " << weaponId << " and frame: " << (weaponId-1)*(GUN_SLICES)+animationStatus << " the: " << framesAlreadyPlayed << "-th time" << std::endl;
    if (animationStatus >= 5) {
      animationStatus = 0;
      this->player->stopShooting();
    }
  }
  this->gun->updateFrame((weaponId-1)*(GUN_SLICES)+animationStatus);
  int x, y, width, height;
  this->window->getWindowSize(&x, &y);
  this->manager.getTextureSizeWithId(GUNSPRITESROW, &width, &height);
  this->gun->setSlideWidth(&width);
  float aspectRatio = float(height) / float(width);
  width = x / 2;
  height = width * aspectRatio;
  y -= (y + height) / 2;
  x -= (x + width) / 2;
  Area destArea(x, 72*y/100, width , height);
  this->gun->renderActualFrame(destArea, GUNSPRITESROW);
}

void Hud::updateHudGun() {
  this->hudgun->updateFrame();
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
  window(window), renderer(window->getRenderer()), player(player), manager(manager), animationStatus(0), framesAlreadyPlayed(0){
  if (TTF_Init() < 0 || !(this->font = TTF_OpenFont(FONT_PATH GAME_FONT, 100))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  this->bjface = new SdlAnimation(manager, FACES_PER_IMG);
  this->hudgun = new SdlAnimation(manager, GUNS_IN_HUD);
  this->gun = new SdlAnimation(manager, FRAMES_PER_GUN_ANIMATION);
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

void Hud::updateFpsCounter(int fps) {
  this->fps = fps;
}

void Hud::renderFpsCounter() {
  int x, y;
  this->window->getWindowSize(&x, &y);
  int width = x / 16;
  int height = y / 6;
  x -= width + 893 * x / 1000;
  x += x / 11;
  if (this->fps < 100){
    width -= width / 160;
    x += x / 50;
  }
  y -= height - y / 275;
  SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height};
  this->renderText(std::to_string(this->fps).c_str(), &rect);
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
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = nullptr;
  SDL_Color color = {GREY};
  if (!(surface = TTF_RenderText_Solid(this->font, text, color))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  if (!(texture = SDL_CreateTextureFromSurface(this->renderer, surface))) {
    throw SdlException(TTF_INIT_ERROR, TTF_GetError());
  }
  SDL_RenderCopy(this->renderer, texture, NULL, rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

Hud::~Hud() {
  delete this->bjface;
  delete this->hudgun;
  TTF_CloseFont(this->font);
  TTF_Quit();
}
