#ifndef HUD_H_
#define HUD_H_

#include <SDL2/SDL_ttf.h>
#include "sdlwindow.h"
#include "player.h"
class Hud {
 private:
  SdlWindow* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Texture* texture;
  Player* player;
  void renderText(const char* text, SDL_Rect* rect);
 public:
  void renderFps(int fps);
  void renderLifes();
  void renderHealth();
  ~Hud();
  Hud(SdlWindow* window, Player* player);
};

#endif  // HUD_H_
