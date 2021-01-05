#include "sdlanimation.h"

#include "area.h"

#include <iostream>

void SdlAnimation::updateFrame() {
  this->pos++;
  this->pos %= this->picsPerAnimation;
}

void SdlAnimation::setSlideWidth(int* width) {
  *width /= this->picsPerAnimation;
}

void SdlAnimation::renderActualFrame(Area& destArea, int textureId) {
  int w, h;
  this->manager.getTextureSizeWithId(textureId, &w, &h);
  w /= this->picsPerAnimation;
  Area srcArea(w * pos, 0, w, h);
  this->manager.render(textureId, srcArea, destArea);
}
