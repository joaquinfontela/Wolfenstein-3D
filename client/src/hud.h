#ifndef HUD_H_
#define HUD_H_

#include <SDL2/SDL_ttf.h>
#include "sdlwindow.h"
#include "sdlanimation.h"
#include "player.h"

class Hud {
 private:
  SdlWindow* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  Player* player;
  TextureManager& manager;
  SdlAnimation* hudgun;
  SdlAnimation* bjface;
  SdlAnimation* gun;
  short animationStatus;
  int fps;
  int framesAlreadyPlayed;
  void renderText(const char* text, SDL_Rect* rect);
  void renderFpsCounter();
  void renderLifes();
  void renderFace();
  void renderHealth();
  void renderTypeOfGun();
  void renderGun();
 public:
  void updateFpsCounter(int fps);
  void update();
  void updateHudGun();
  void updateBjFace();
  ~Hud();
  Hud(SdlWindow* window, Player* player, TextureManager& manager);
};

#endif  // HUD_H_
