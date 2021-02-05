#include "../includes/sdlanimation.h"

#include "../includes/area.h"

void SdlAnimation::updateFrame() {
  this->pos++;
  this->pos %= this->picsPerAnimation;
}

void SdlAnimation::updateFrame(int newpos) {
  this->pos = newpos;
  this->pos %= this->picsPerAnimation;
}

void SdlAnimation::setSlideWidth(int* width) {
  *width /= this->picsPerAnimation;
}

void SdlAnimation::renderActualFrame(Area& destArea, int textureId) {
  int w, h;
  this->manager.getTextureSizeWithId(textureId, &w, &h);
  w /= this->picsPerAnimation;
  Area srcArea(w * pos + (pos - 1), 0, w, h);
  this->manager.render(textureId, srcArea, destArea);
}
