#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <SDL2/SDL.h>

#include <map>
#include <string>

#include "area.h"
#include "sdlwindow.h"
#include "sdltexture.h"

class TextureManager{
 public:
  ~TextureManager();
  TextureManager(SdlWindow* window) : window(window) {}
  void loadTextures();
  void render(int id, const Area& srcArea, const Area& destArea);
  void renderAll(int id, const Area& destArea);
  void loadTexture(int id, SdlTexture* texture);
  void getWindowSize(int* w, int* h);
  void getTextureSizeWithId(int id, int* w, int* h);
  void renderText(const char* text, SDL_Rect* rect);
 private:
  SdlWindow* window;
  void garbageCollector();
  bool loadAndCheckTexture(int i, const std::string& name);
  std::map<int,SdlTexture*> textures;
};

#endif  // TEXTUREMANAGER_H_
