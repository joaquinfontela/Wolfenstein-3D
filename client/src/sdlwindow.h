#ifndef SDLWINDOW_H_
#define SDLWINDOW_H_
#include "area.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SdlWindow {
 public:
  SdlWindow(int width, int height);
  ~SdlWindow();
  SdlWindow(SdlWindow&& other);
  SdlWindow& operator=(SdlWindow&& other);
  void fill(int r, int g, int b, int alpha);
  void fill();
  void fillTransparent(int r, int g, int b);
  void render();
  SDL_Renderer* getRenderer() const;

 private:
  void killRenderer();
  void killWindow();
  SDL_Window* window;
  SDL_Renderer* renderer;
};

#endif  // SDLWINDOW_H_
