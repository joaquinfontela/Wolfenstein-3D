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
  std::cout << "w: " << w << " pos-1: " << pos - 1 << std::endl;
  Area srcArea(w * pos + (pos - 1), 0, w, h);
  this->manager.render(textureId, srcArea, destArea);
}
