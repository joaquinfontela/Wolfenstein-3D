#include "../includes/player.h"

#include <math.h>

#include <iostream>

#include "../includes/clientprotocol.h"

bool Player::hasKey() {
  return key;
  // return this->hasTheKey;
}

bool Player::isPlayer() { return true; }

bool Player::isSprite() { return false; }

static bool sameSign(double a, double b) {
  return ((a <= 0 && b <= 0) || (a > 0 && b > 0));
}

double Player::calculateDist(Player* other) {
  return sqrt(pow(this->x - other->x, 2) + pow(this->y - other->y, 2));
}

double Player::calculateDist(int otherx, int othery) {
  return sqrt(pow(this->x - otherx, 2) + pow(this->y - othery, 2));
}

bool Player::hasThisUniqueId(int otherid) { return false; }

bool Player::isShooting() { return this->shooting; }

bool Player::isMoving() { return this->moving; }

void Player::stopMoving() { this->moving = false; }

Player::Player(PlayerData& info) {
  this->x = info.posX;
  this->y = info.posY;
  this->weaponId = info.weaponID;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->id = 3;
  this->planeX = 0;
  this->planeY = 0;
  this->playerID = info.playerID;
  this->lives = info.lives;
  this->health = info.health;
  this->bullets = info.bullets;
  this->score = info.score;
  this->key = info.hasKey;
  this->hasTheKey = false;
  this->healthdown = false;
  this->totalFrames = TIME_PER_ANIMATION_SLIDE * 5;
  this->framesPerAnimation = 1;
  this->hasToBeDeleted = false;
  this->restartAnimationStats();
}

void Player::restartAnimationStats() {
  this->minigunShooting = false;
  this->animatingShooting = false;
  this->animatingMovement = false;
  this->shooting = false;
  this->moving = false;
  this->timePassed = 0;
  this->frames = 0;
}

void Player::update(PlayerData& info) {
  this->moving = ((fabs(this->x - info.posX) > 0.05) ||
                  (fabs(this->y - info.posY) > 0.05));
  this->healthdown = (this->health > info.health);
  this->x = info.posX;
  this->y = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->lives = info.lives;
  this->health = info.health;
  this->weaponId = info.weaponID;
  this->bullets = info.bullets;
  this->score = info.score;
  this->key = info.hasKey;

  double oldPlaneX = planeX;
  double cosVal = cos(info.rotSpeed);
  double sinVal = sin(info.rotSpeed);

  this->planeX = (this->planeX * cosVal) - (this->planeY * sinVal);
  this->planeY = (oldPlaneX * sinVal) + (this->planeY * cosVal);
}

int Player::getSoldierId() {
  if (this->shooting ||
      this->animatingShooting) {  // Que cuando termine la animación setee el
                                  // booleano en false.
    this->frames = (this->timePassed > 125) + (this->timePassed > 250) +
                   (this->timePassed > 375);
    return GET_SHOOTING_ANIMATION_FROM_GUNID(this->weaponId);
    this->animatingShooting = true;
  } else if (this->moving || this->animatingMovement) {
    this->frames = (this->timePassed > 100) + (this->timePassed > 200) +
                   (this->timePassed > 300) + (this->timePassed > 400);
    return GET_MOVING_ANIMATION_FROM_GUNID(this->weaponId);
    this->animatingMovement = true;
  } else {
    this->frames = 0;
    return GET_STANDING_IMG_FROM_GUNID(this->weaponId);
  }
}

void Player::draw(TextureManager& manager, double posX, double posY,
                  double dirX, double dirY, double planeX, double planeY,
                  double* distanceBuffer, float diff) {

  this->timePassed += diff;
  int spriteScreen, spriteWidth, spriteHeight, drawStart, drawEnd, width,
      height, preCalcdValue1, preCalcdValue2, preCalcdValue3,
      spriteId = this->getSoldierId();
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
    int playerStripe = int(((stripe - preCalcdValue1) << 14) / spriteWidth) >> 8;
    if (playerStripe < 0) continue;

    if (transformY > 0 && stripe > 0 && transformY < distanceBuffer[stripe]) {
      srcArea.update(playerStripe + (this->frames << 6), 0, 1, preCalcdValue3);
      destArea.update(stripe, preCalcdValue2, 1, spriteHeight);
      manager.render(spriteId, srcArea, destArea);
    }
  }
  if (this->timePassed > 500) {
    this->restartAnimationStats();
  }
}

void Player::startShooting() {
   this->shooting = true;
   this->minigunShooting = true;
 }

void Player::stopShooting() {
  this->shooting = false;
  this->minigunShooting = false;
}
