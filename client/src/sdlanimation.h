#ifndef SDLANIMATION_H_
#define SDLANIMATION_H_

#include "texturemanager.h"
#include "drawable.h"
#include "area.h"

class SdlAnimation : public Drawable {
 public:
  SdlAnimation(TextureManager& manager, int slides) :
    pos(0), textureId(textureId), manager(manager) , picsPerAnimation(slides) {}
  void updateFrame(int newpos);
  void updateFrame();
  void setSlideWidth(int* width);
  void renderActualFrame(Area& destArea, int textureId);
 private:
  int pos;
  int textureId;
  TextureManager& manager;
  int picsPerAnimation;
};

#endif  // SDLANIMATION_H_
