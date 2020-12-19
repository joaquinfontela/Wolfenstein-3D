#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <map>

#include "area.h"
#include "sdltexture.h"

class TextureManager{
 public:
  void renderAll(int img, Area destArea);
  void render(int img, Area srcArea, Area destArea);
  void loadTexture(int img, SdlTexture* texture);
 private:
  std::map<int,SdlTexture*> textures;
};

#endif  // TEXTUREMANAGER_H_
