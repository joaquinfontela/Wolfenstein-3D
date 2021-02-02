#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include "area.h"
#include <SDL2/SDL_ttf.h>
#include "sdltexture.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SdlWindow {
 public:
  SdlWindow(int width, int height);
  ~SdlWindow();
  void fill(int r, int g, int b, int alpha);
  void fill();
  void fillWolfenstein();
  void fillTransparent(int r, int g, int b);
  void render();
  void getWindowSize(int* w, int* h);
  void renderText(const char* text, SDL_Rect* rect);
  SDL_Renderer* getRenderer() const;
  void playOrStopAudio();
 private:
  void killRenderer();
  void killWindow();
  void killAudio();
  int width;
  TTF_Font* font;
  int height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SdlTexture* ceilingPixel;
};

#endif
