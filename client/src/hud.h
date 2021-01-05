#ifndef HUD_H_
#define HUD_H_

#include <SDL2/SDL_ttf.h>
#include "sdlwindow.h"
#include "sdlanimation.h"
#include "player.h"

class Hud {
 private:
  SdlWindow* window;
  SdlAnimation* bjface;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Texture* texture;
  Player* player;
  TextureManager& manager;
  void renderText(const char* text, SDL_Rect* rect);
  void renderFps(int fps);
  void renderLifes();
  void renderFace();
  void renderHealth();
 public:
  void update(int fps);
  void updateBjFace();
  ~Hud();
  Hud(SdlWindow* window, Player* player, TextureManager& manager);
};

#endif  // HUD_H_
