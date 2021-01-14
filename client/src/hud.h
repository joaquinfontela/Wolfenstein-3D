#ifndef HUD_H_
#define HUD_H_

#include <SDL2/SDL_ttf.h>
#include "sdlwindow.h"
#include "sdlanimation.h"
#include "player.h"

class Hud {
 private:
  int width, height;
  SdlWindow* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  Player* player;
  TextureManager& manager;
  SdlAnimation* hudgun;
  SdlAnimation* bjface;
  SdlAnimation* gun;
  short animationStatus;
  short movementStatus;
  int fps;
  int framesAlreadyPlayed;
  void renderText(const char* text, SDL_Rect* rect);
  void renderFpsCounter();
  void renderLifes();
  void renderFace();
  void renderHealth();
  void renderTypeOfGun();
  void renderGun();
  void renderGunWithShifts(int dx = 0, int dy = 0, int updatefreq = 16);
  void renderGunWithMovement();
  void renderBorder();
  void renderBullets();
 public:
  void updateFpsCounter(int fps);
  void update();
  void updateHudGun();
  void updateBjFace();
  ~Hud();
  Hud(SdlWindow* window, Player* player, TextureManager& manager);
};

#endif  // HUD_H_
