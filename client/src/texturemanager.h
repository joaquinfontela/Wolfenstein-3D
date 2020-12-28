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
  void render(int id, Area srcArea, Area destArea);
  void renderAll(int id, Area destArea);
  void loadTexture(int id, SdlTexture* texture);
 private:
  SdlWindow* window;
  void garbageCollector();
  bool loadAndCheckTexture(int n, const std::string& name);
  std::map<int,SdlTexture*> textures;
};

#endif  // TEXTUREMANAGER_H_
