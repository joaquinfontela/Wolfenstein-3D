#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include "area.h"

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
  SDL_Renderer* getRenderer() const;
  void playOrStopAudio();
 private:
  void killRenderer();
  void killWindow();
  void killAudio();
  int width;
  int height;
  SDL_Window* window;
  SDL_Renderer* renderer;
};

#endif
