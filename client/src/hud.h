#ifndef HUD_H_
#define HUD_H_

#include <SDL2/SDL_ttf.h>
#include "sdlwindow.h"
#include "player.h"
class Hud {
 private:
  SdlWindow* window;
  TTF_Font* font;
  SDL_Texture* texture;
  Player* player;
  SdlTexture* text;
 public:
  void renderText();
  ~Hud();
  Hud(SdlWindow* window, Player* player);
};

#endif  // HUD_H_
