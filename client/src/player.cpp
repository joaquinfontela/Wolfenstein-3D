#include "player.h"
#include <math.h>

#define BLOCKSIZE 64
#define PI 3.141592654

static bool sameSign(double a, double b) {
  return ((a <= 0 && b <= 0) || (a > 0 && b > 0));
}

int Player::getSoldierId(double x, double y, double dirX, double dirY) {
  double angle = abs(atan2(this->y - y, this->x - x)) * 180 / PI;

  if (angle > 0 && angle < 22.5) // Frente
    return 8;
  else if (angle < 67.5 && angle > 22.5) // Der-Frente
    return
  else if (angle < 112.5 && angle > 67.5) // Der
    return 9;
  else if (angle > 112.5 && angle < 157.5) // Der-Atrás
    return
  else if (angle < 202.5 && angle > 157.5) // Atrás
    return 10;
  else if (angle > 202.5 && angle > 247.5) // Izq-Atrás
    return
  else if (angle > 292.5 && angle < 247.5) // Izq
    return 11;
  else // Izq-Frente
    return 
}

Player::Player(PlayerData& info) {
  this->x = info.posX;
  this->y = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->id = 3;
  this->planeX = 0;
  this->planeY = 0;
  this->playerID = info.playerID;
}

void Player::update(PlayerData& info) {
  this->x = info.posX;
  this->y = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;

  double oldPlaneX = planeX;
  double cosVal = cos(info.rotSpeed);
  double sinVal = sin(info.rotSpeed);

  this->planeX = (this->planeX * cosVal) - (this->planeY * sinVal);
  this->planeY = (oldPlaneX * sinVal) + (this->planeY * cosVal);
}

void Player::update(double posX, double posY, double dirX, double dirY) {
  this->x = posX;
  this->y = posY;
  this->dirX = dirX;
  this->dirY = dirY;
}

void Player::draw(TextureManager& manager, double posX, double posY, double dirX, double dirY, double planeX, double planeY, double* zBuffer) {

  int width, height;
  manager.getWindowSize(&width, &height);

  double spriteX = this->x - posX;
  double spriteY = this->y - posY;

  double invDet = 1.0 / (planeX * dirY - dirX * planeY);

  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

  int spriteScreenX = int((width / 2) * (1 + transformX / transformY));

  int spriteHeight = abs(int(height / (transformY)));

  int drawStartY = -spriteHeight / 2 + height / 2;
  if (drawStartY < 0) drawStartY = 0;
  int drawEndY = spriteHeight / 2 + height / 2;
  if (drawEndY >= height) drawEndY = height - 1;

  int spriteWidth = abs(int (height / (transformY)));
  int drawStartX = -spriteWidth / 2 + spriteScreenX;
  if (drawStartX < 0) drawStartX = 0;
  int drawEndX = spriteWidth / 2 + spriteScreenX;
  if (drawEndX >= width) drawEndX = width - 1;

  int spriteId = 3;
  /*double angle = atan2(this->dirY - dirY, this->dirX - dirX);
  if (angle < 2*PI) angle += PI;
  if (angle > 0 && angle < PI) spriteId = 10;*/

  bool sameSignX = sameSign(this->dirX, dirX);
  bool sameSignY = sameSign(this->dirY, dirY);
  bool diffSignX = !sameSignX;
  bool diffSignY = !sameSignY;

  if (diffSignX && diffSignY)
    spriteId = 11;
  else if (sameSignX && diffSignY)
    spriteId = 8;
  else if (diffSignX && sameSignY)
    spriteId = 9;
  else
    spriteId = 10;

  for (int stripe = drawStartX; stripe < drawEndX; stripe++){
    int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;

    if (transformY > 0 && stripe > 0 && stripe < width && transformY < zBuffer[stripe]){
      Area srcArea(texX, 0, 1, (spriteHeight < BLOCKSIZE) ? BLOCKSIZE : spriteHeight);
      Area destArea(stripe, (height - spriteHeight) / 2, 1, spriteHeight);
      manager.render(spriteId, srcArea, destArea);
    }
  }
}
