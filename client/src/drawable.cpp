#include "../includes/drawable.h"

#include <math.h>

#include <iostream>

#include "../includes/clientprotocol.h"

bool Drawable::isSprite() { return true; }

bool Drawable::hasThisUniqueId(int otherid) {
  return (this->uniqueid == otherid);
}

// No square root for efficency sake.
void Drawable::loadDistanceWithCoords(int px, int py) {
  this->dist = pow(px - this->x, 2) + pow(py - this->y, 2);
}

bool Drawable::operator<(Drawable& other) { return this->dist > other.dist; }

bool Drawable::isPlayer() { return false; }

void Drawable::calculateDrawingData(int& spriteScreen, int& spriteWidth,
                                    int& spriteHeight, int& drawStart,
                                    int& drawEnd, double& transformY,
                                    double posX, double posY, double planeX,
                                    double planeY, double dirX, double dirY,
                                    int width, int height) {
  double spriteX = this->x - posX;
  double spriteY = this->y - posY;

  double inverseDeterminant = 1.0 / (planeX * dirY - dirX * planeY);

  double transformX = inverseDeterminant * (dirY * spriteX - dirX * spriteY);
  transformY = inverseDeterminant * (-planeY * spriteX + planeX * spriteY);

  spriteScreen = int((width >> 1) * (1 + transformX / transformY));

  spriteHeight = abs(int(height / (transformY)));
  spriteWidth = abs(int(height / (transformY)));
  drawStart = (spriteScreen - spriteWidth) >> 1;
  drawStart = !(drawStart < 0) * drawStart;
  drawEnd = spriteWidth / 2 + spriteScreen;
  bool condition = (drawEnd >= width);
  drawEnd = condition * (width - 1) + !condition * drawEnd;
}

bool Drawable::isContained(double* distanceBuffer, double posX, double posY,
                           double dirX, double dirY, double planeX,
                           double planeY, int width, int height) {
  int spriteScreen, spriteWidth, spriteHeight, drawStart, drawEnd;
  double transformY;

  this->calculateDrawingData(spriteScreen, spriteWidth, spriteHeight, drawStart,
                             drawEnd, transformY, posX, posY, planeX, planeY,
                             dirX, dirY, width, height);
  drawEnd = (drawEnd < width) ? drawEnd : width;

  int preCalcdValue = (spriteScreen - (spriteWidth >> 1));

  for (int stripe = drawStart; stripe < drawEnd; stripe++) {
    int drawableStripe = int(((stripe - preCalcdValue) << 14) / spriteWidth) >> 8;
    if (drawableStripe < 0) continue;
    if (transformY > 0 && stripe > 0 && transformY < distanceBuffer[stripe]) {
      return true;
    }
  }
  return false;
}

void Drawable::getPreCalculatedValues(int& preCalcdValue1, int& preCalcdValue2,
                            int& preCalcdValue3, bool& tooFar, int spriteScreen,
                            int spriteHeight, int spriteWidth, int height) {
  preCalcdValue1 = (spriteScreen - (spriteWidth >> 1));
  preCalcdValue2 = (height - spriteHeight) >> 1;
  tooFar = (spriteHeight < BLOCKSIZE);
  preCalcdValue3 = BLOCKSIZE * tooFar + spriteHeight * !tooFar;
}

void Drawable::draw(TextureManager& manager, double posX, double posY,
                    double dirX, double dirY, double planeX, double planeY,
                    double* distanceBuffer, float diff) {

  int spriteScreen, spriteWidth, spriteHeight, drawStart, drawEnd, width,
  height, preCalcdValue1, preCalcdValue2, preCalcdValue3;
  double transformY;
  bool tooFar;

  manager.getWindowSize(&width, &height);

  this->calculateDrawingData(spriteScreen, spriteWidth, spriteHeight, drawStart,
                             drawEnd, transformY, posX, posY, planeX, planeY,
                             dirX, dirY, width, height);
  this->getPreCalculatedValues(preCalcdValue1, preCalcdValue2, preCalcdValue3,
                               tooFar, spriteScreen, spriteHeight, spriteWidth, height);

  drawEnd = (drawEnd < width) ? drawEnd : width;
  for (int stripe = drawStart; stripe < drawEnd; stripe++) {
    int drawableStripe = int(((stripe - preCalcdValue1) << 14) / spriteWidth) >> 8;
    if (drawableStripe < 0) continue;

    if (transformY > 0 && stripe > 0 && transformY < distanceBuffer[stripe]) {
      srcArea.update(drawableStripe, 0, 1, preCalcdValue3);
      destArea.update(stripe, preCalcdValue2, 1, spriteHeight);
      manager.render(this->id, srcArea, destArea);
    }
  }
}
