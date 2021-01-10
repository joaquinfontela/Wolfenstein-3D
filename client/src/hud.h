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
  int animationStatus;
  void renderText(const char* text, SDL_Rect* rect);
  void renderFps(int fps);
  void renderLifes();
  void renderFace();
  void renderHealth();
  void renderTypeOfGun();
  void renderGun();
 public:
  void update(int fps);
  void updateHudGun();
  void updateBjFace();
  ~Hud();
  Hud(SdlWindow* window, Player* player, TextureManager& manager);
};

#endif  // HUD_H_
