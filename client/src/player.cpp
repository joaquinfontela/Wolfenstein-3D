#include "player.h"
#include <math.h>

Player::Player(PlayerData& info) {
  this->posX = info.posX;
  this->posY = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->id = info.playerID;
  this->planeX = 0;
  this->planeY = 0;
}

void Player::update(PlayerData& info) {
  this->posX = info.posX;
  this->posY = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;

  double oldPlaneX = planeX;
  double cosVal = cos(info.rotSpeed);
  double sinVal = sin(info.rotSpeed);

  this->planeX = (this->planeX * cosVal) - (this->planeY * sinVal);
  this->planeY = (oldPlaneX * sinVal) + (this->planeY * cosVal);
}

void Player::update(double posX, double posY, double dirX, double dirY) {
  this->posX = posX;
  this->posY = posY;
  this->dirX = dirX;
  this->dirY = dirY;
}
