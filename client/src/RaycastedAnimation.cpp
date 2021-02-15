#include "../includes/RaycastedAnimation.h"

#include <iostream>

#include "../includes/area.h"
#include "../includes/clientprotocol.h"

void RaycastedAnimation::draw(TextureManager& manager, double posX, double posY,
                              double dirX, double dirY, double planeX,
                              double planeY, double* distanceBuffer,
                              float diff) {

  this->timePassed += diff;
  int spriteScreen, spriteWidth, spriteHeight, drawStart, drawEnd, width,
      height, preCalcdValue1, preCalcdValue2, preCalcdValue3;
  double transformY;
  manager.getWindowSize(&width, &height);
  bool tooFar;

  this->calculateDrawingData(spriteScreen, spriteWidth, spriteHeight, drawStart,
                             drawEnd, transformY, posX, posY, planeX, planeY,
                             dirX, dirY, width, height);

  this->getPreCalculatedValues(preCalcdValue1, preCalcdValue2, preCalcdValue3,
                             tooFar, spriteScreen, spriteHeight, spriteWidth, height);

  drawEnd = (drawEnd < width) ? drawEnd : width;
  for (int stripe = drawStart; stripe < drawEnd; stripe++) {
    int animationStripe =
        int(((stripe - preCalcdValue1) << 14) / spriteWidth) >> 8;
    if (animationStripe < 0 || this->timePassed > this->totalFrames)
      continue;
    else if (floor(this->timePassed / TIME_PER_ANIMATION_SLIDE) > this->frames)
      this->frames = (this->frames + 1) % this->framesPerAnimation;


    if (transformY > 0 && stripe > 0 && transformY < distanceBuffer[stripe]) {
      srcArea.update(animationStripe + (this->frames << 6), 0, 1,
                     preCalcdValue3);
      destArea.update(stripe, preCalcdValue2, 1, spriteHeight);
      manager.render(this->id, srcArea, destArea);
    }
  }

  if (this->timePassed > this->totalFrames) {
    this->hasToBeDeleted = true;
  }
}
