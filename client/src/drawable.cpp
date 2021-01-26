#include "drawable.h"
#include "clientprotocol.h"
#include <math.h>
#include <iostream>

bool Drawable::isSprite() {
  return true;
}

bool Drawable::hasThisUniqueId(int otherid) {
  return (this->uniqueid == otherid);
}

// No square root for efficency sake.
void Drawable::loadDistanceWithCoords(int px, int py){
  this->dist = pow(px - this->x, 2) + pow(py - this->y, 2);
}

bool Drawable::operator<(Drawable& other) {
  return this->dist > other.dist;
}

void Drawable::draw(TextureManager& manager, double posX, double posY, double dirX,
                    double dirY, double planeX, double planeY, double* zBuffer, float diff) {

  int width, height;
  manager.getWindowSize(&width, &height);

  double spriteX = this->x - posX;
  double spriteY = this->y - posY;

  double invDet = 1.0 / (planeX * dirY - dirX * planeY);

  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

  int spriteScreenX = int((width >> 1) * (1 + transformX / transformY));

  int spriteHeight = abs(int(height / (transformY)));
  int drawStartY = (height - spriteHeight) >> 1;
  drawStartY = !(drawStartY < 0) * drawStartY;
  int drawEndY = (spriteHeight + height) >> 1;
  bool condition = (drawEndY >= height);
  drawEndY = condition * (height - 1) + !condition * drawEndY;

  int spriteWidth = abs(int(height / (transformY)));
  int drawStartX = (spriteScreenX - spriteWidth) >> 1;
  drawStartX = !(drawStartX < 0) * drawStartX;
  int drawEndX = spriteWidth / 2 + spriteScreenX;
  condition = (drawEndX >= width);
  drawEndX = condition * (width - 1) + !condition * drawEndX;

  int preCalcdValue1 = (spriteScreenX - (spriteWidth >> 1));
  int preCalcdValue2 = (height - spriteHeight) >> 1;
  condition = (spriteHeight < BLOCKSIZE);
  int preCalcdValue3 = BLOCKSIZE * condition + spriteHeight * !condition;

  for (int stripe = drawStartX; stripe < drawEndX; stripe++){
    int texX = int(((stripe - preCalcdValue1) << 14) / spriteWidth) >> 8;
    if (texX < 0) continue;

    if (transformY > 0 && stripe > 0 && stripe < width && transformY < zBuffer[stripe]){
      srcArea.update(texX, 0, 1, preCalcdValue3);
      destArea.update(stripe, preCalcdValue2, 1, spriteHeight);
      manager.render(this->id, srcArea, destArea);
    }
  }
}
