#include "../../../../includes/Model/Item/Weapon/Weapon.h"

Weapon::Weapon(unsigned int uniqueId, unsigned int minDamagePerBullet,
               int maxDamagePerBullet) {
  this->uniqueId = uniqueId;
  this->minDamagePerBullet = minDamagePerBullet;
  this->maxDamagePerBullet = maxDamagePerBullet;
}

unsigned int Weapon::getRandomDamage() {
  return ((rand() % this->maxDamagePerBullet) + this->minDamagePerBullet);
}