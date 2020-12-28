#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <map>

#include "area.h"
#include "sdltexture.h"

class TextureManager{
 public:
  void renderAll(int id, Area destArea);
  void render(int id, Area srcArea, Area destArea);
  void loadTexture(int id, SdlTexture* texture);
 private:
  std::map<int,SdlTexture*> textures;
};

#endif  // TEXTUREMANAGER_H_
