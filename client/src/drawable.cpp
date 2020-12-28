#include "drawable.h"

#include <math.h>

#define HEIGHT 600
#define WIDTH 800

void Drawable::loadDistanceWithCoords(int px, int py){
  this->dist = pow(px - this->x, 2) + pow(py - this->y, 2);
}

bool Drawable::operator<(Drawable& other) {
  return this->dist > other.dist;
}

void Drawable::draw(TextureManager& manager, double posX, double posY, double dirX, double dirY, double planeX, double planeY, double* zBuffer) {

  double spriteX = this->x - posX;
  double spriteY = this->y - posY;

  double invDet = 1.0 / (planeX * dirY - dirX * planeY);

  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

  int spriteScreenX = int((WIDTH / 2) * (1 + transformX / transformY));

  int spriteHeight = abs(int(HEIGHT / (transformY)));

  int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
  if (drawStartY < 0) drawStartY = 0;
  int drawEndY = spriteHeight / 2 + HEIGHT / 2;
  if (drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

  int spriteWidth = abs(int (HEIGHT / (transformY)));
  int drawStartX = -spriteWidth / 2 + spriteScreenX;
  if (drawStartX < 0) drawStartX = 0;
  int drawEndX = spriteWidth / 2 + spriteScreenX;
  if (drawEndX >= WIDTH) drawEndX = WIDTH - 1;

  for (int stripe = drawStartX; stripe < drawEndX; stripe++){
    int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;

    if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < zBuffer[stripe]){
      Area srcArea(texX, 0, 1, spriteHeight);
      Area destArea(stripe, (HEIGHT - spriteHeight) / 2, 1, spriteHeight);
      manager.render(this->id, srcArea, destArea);
    }
  }
}
