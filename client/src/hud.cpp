#include "../includes/hud.h"

#include <SDL2/SDL.h>
#include <math.h>

#include <iostream>

#include "../includes/area.h"
#include "../includes/clientprotocol.h"
#include "../includes/player.h"
#include "../includes/sdlexception.h"
#include "../includes/sdltexture.h"

#define SIZE 25
#define FACES_PER_IMG 3
#define GUNS_IN_HUD 5
#define FRAMES_PER_GUN_ANIMATION 25
#define FRAMES_PER_MOVEMENT 20
#define GUN_SLICES FRAMES_PER_GUN_ANIMATION / 5

void Hud::update() {
  this->renderGun();
  this->renderBorder();
  this->renderFpsCounter();
  this->renderLifes();
  this->renderHealth();
  this->renderScore();
  this->renderFace();
  this->renderKey();
  this->renderBullets();
  this->renderTypeOfGun();
  this->renderBloodDamage();
  this->framesAlreadyPlayed++;
}

void Hud::renderBloodDamage() {
  int healthdown;
  if (!(healthdown = player->healthdown)) return;
  this->manager.renderComplete(DAMAGE_HUD);
  player->healthdown = (healthdown + 1) % BLOOD_FRAMES;
}

void Hud::renderKey() {
  if (!player->hasKey()) return;
  int x, y;
  x = this->screenWidth;
  y = this->screenHeight;
  int width, height;
  this->manager.getTextureSizeWithId(HUDKEY, &width, &height);
  area.update((x * 547) / 720.0, (517 * y) / 600.0, (x >> 4) / 3, (y >> 2) / 3);
  this->manager.renderAll(HUDKEY, area);
}

void Hud::renderScore() {
  int x, y;
  int score = player->score;
  x = this->screenWidth;
  y = this->screenHeight;
  int width = x / 30;
  int height = y / 6;
  x -= width + 4 * x / 5;
  y -= height - y / 200;
  if (score > 9999) {
    width *= 4;
    x -= x / 25;
  } else if (score > 999) {
    width *= 3;
    x += x / 30;
  } else if (score > 99) {
    width *= 2;
    x += 13 * x / 100;
  } else if (score > 9) {
    width *= 2;
    x += 3 * x / 25;
  } else {
    x += 11 * x / 50;
  }
  SDL_Rect rect = {.x = x, .y = y, .w = width, .h = height};
  this->manager.renderText(std::to_string(score).c_str(), &rect);
}

void Hud::updateGunId() { this->weaponId = this->player->weaponId; }

void Hud::renderBorder() {
  Area d2(0, 0, this->screenWidth, this->screenHeight);
  this->manager.renderAll(HUD_SPRITE, d2);
}

void Hud::renderTypeOfGun() {
  this->updateGunId();
  this->hudgun.animation->updateFrame(weaponId - 1);
  int x, y, width, height;
  y = this->screenHeight;
  x = this->screenWidth;
  this->manager.getTextureSizeWithId(HUDGUNS, &width, &height);
  this->hudgun.animation->setSlideWidth(&width);
  float aspectRatio = float(height) / float(width);
  width = (x * 9) / 50;
  height = width * aspectRatio;
  area.update((63 * x) / 80, (33 * y) / 40, width, height);
  this->hudgun.animation->renderActualFrame(area, HUDGUNS);
}

void Hud::renderGun() {
  if (player->isMoving()) {
    this->renderGunWithMovement();
    if (this->movementStatus > FRAMES_PER_MOVEMENT) {
      player->stopMoving();
      this->movementStatus = 0;
    }
  } else {
    this->renderGunWithShifts();
  }
}
/*
 * Let's say that the number of frames that our animation has is Z.
 * If our animation lasted Z frames and we wanted to play it in one second,
 * then we would have to update the frames every FPS/Z number of iterations.
 * Now, if we had Z frames that would have to be played in T' seconds, every
 * frame of the animation would have to be updated every (FPS * T')/Z
 * iterations.
 */

// This equation is the solution to the "Lemniscate of Gerono" equation.
void Hud::renderGunWithMovement() {
  float sinval = sin(movementStatus >> 2);
  int dx = sinval * 10;
  int dy = sinval * cos(movementStatus >> 2) * 6;
  int updatefreq = this->fps / (FRAMES_PER_MOVEMENT << 1);
  this->renderGunWithShifts(dx, dy + 2, updatefreq);
  if (!(updatefreq) || !(this->framesAlreadyPlayed % updatefreq))
    movementStatus++;
}

void Hud::renderBullets() {
  int x, y;
  int bullets = player->bullets;
  y = this->screenHeight;
  x = this->screenWidth;
  int width = x / 30;
  int height = y / 6;
  x -= width + 300 * x / 1000;
  y -= height - y / 200;
  if (bullets > 99) {
    width *= 2;
    x -= x / 100;
  } else if (bullets > 9) {
    width *= 2;
    x -= x / 100;
  } else {
    x += x / 50;
  }
  SDL_Rect rect = {.x = x, .y = y, .w = width, .h = height};
  this->manager.renderText(std::to_string(bullets).c_str(), &rect);
}

void Hud::playMyShootingSound() {
  int weaponId = this->player->weaponId;
  int soundId = GET_WEAPON_SOUND(weaponId);
  this->audiomanager.playOnMaxVolumeWithId(soundId);
}

int Hud::getGunFrame() {
  /*bool minigunShooting = (this->player->isShooting() && weaponId == CHAINGUN);
  if (minigunShooting && animationStatus == 4 && this->player->minigunShooting) {
    animationStatus = 2;
  }*/
  if (animationStatus == 2) this->playMyShootingSound();
  return ((this->weaponId - 1) * (GUN_SLICES) + animationStatus);
}

void Hud::renderGunWithShifts(int dx, int dy, int updatefreq) {
  if (this->player->isShooting() &&
      (!(this->fps >> 4) || !(this->framesAlreadyPlayed % (this->fps >> 4)))) {
    // This ^^^^^ is there if this->fps < updatefreq
    // which could result in a zero division error.
    animationStatus++;
    if (animationStatus >= 5) {
      animationStatus = 0;
      this->player->stopShooting();
    }
  }
  this->gun.animation->updateFrame(this->getGunFrame());
  int x, y, width, height;
  y = this->screenHeight;
  x = this->screenWidth;
  //  this->manager.getTextureSizeWithId(GUNSPRITESROW, &width, &height);
  width = 1622;
  height = 38;
  this->gun.animation->setSlideWidth(&width);

  float aspectRatio = float(height) / float(width);
  width = x >> 1;
  height = width * aspectRatio;
  y -= (y + height) >> 1;
  x -= (x + width) >> 1;

  area.update(x + dx, (y * 120) / 91 + dy, width, height);
  this->gun.animation->renderActualFrame(area, GUNSPRITESROW);
}

void Hud::updateHudGun() { this->hudgun.animation->updateFrame(); }

void Hud::renderFace() {
  int health = this->player->health;
  int x, y, width, height, id;
  y = this->screenHeight;
  x = this->screenWidth;
  id = GET_BJ_FACE_FROM_HEALTH(health);
  this->manager.getTextureSizeWithId(id, &width, &height);
  this->bjface.animation->setSlideWidth(&width);
  area.update((x * 67) / 160.0, (503 * y) / 600.0, (7 * x) / 80, (y << 1) / 15);
  this->bjface.animation->renderActualFrame(area, id);
}

void Hud::updateBjFace() { this->bjface.animation->updateFrame(); }

Hud::Hud(Player* player, TextureManager& manager, AudioManager& audiomanager)
    : player(player),
      manager(manager),
      fps(30),
      animationStatus(0),
      framesAlreadyPlayed(0),
      movementStatus(0),
      audiomanager(audiomanager),
      bjface(manager, FACES_PER_IMG),
      hudgun(manager, GUNS_IN_HUD),
      gun(manager, FRAMES_PER_GUN_ANIMATION) {
  this->manager.getWindowSize(&this->screenWidth, &this->screenHeight);
}

void Hud::renderLifes() {
  int x, y;
  y = this->screenHeight;
  x = this->screenWidth;
  int width = x / 30;
  int height = y / 6;
  x -= width + 31 * x / 50;
  y -= height - y / 200;
  SDL_Rect rect = {.x = x, .y = y, .w = width, .h = height};
  this->manager.renderText(std::to_string(player->lives).c_str(), &rect);
}

void Hud::updateFpsCounter(int fps) { this->fps = fps; }

void Hud::renderFpsCounter() {
  int x, y;
  y = this->screenHeight;
  x = this->screenWidth;
  int width = x / 16;
  int height = y / 6;
  x -= width + 893 * x / 1000;
  x += x / 11;
  if (this->fps < 100) {
    width -= width / 160;
    x += x / 50;
  }
  y -= height - y / 275;
  SDL_Rect rect = {.x = x, .y = y, .w = width, .h = height};
  this->manager.renderText(std::to_string(this->fps).c_str(), &rect);
}

void Hud::renderHealth() {
  int x, y;
  y = this->screenHeight;
  x = this->screenWidth;
  int width = x / 16;
  int height = y / 6;
  x -= width + 49 * x / 125;
  if (player->health < 100) {
    width -= width / 160;
    x += x / 53;
  }
  y -= height - y / 275;
  SDL_Rect rect = {.x = x, .y = y, .w = width, .h = height};
  this->manager.renderText(std::to_string(player->health).c_str(), &rect);
}
