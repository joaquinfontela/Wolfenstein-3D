#include "player.h"

void Player::goTo(uint32_t x, uint32_t y, uint32_t angle) {
  this->x = x;
  this->y = y;
  this->viewAngle = angle;
}

int Player::getX() { return this->x; }

int Player::getY() { return this->y; }

int Player::getAngle() { return this->viewAngle; }
