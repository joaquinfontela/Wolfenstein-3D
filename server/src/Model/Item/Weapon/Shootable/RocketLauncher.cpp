#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

unsigned int RocketLauncher::attack() {
  unsigned int damage = 0;
  for (int i = 0; i < 5; i++) {
    damage += this->getRandomDamage();
  }
  ammo -= 5;
  return damage;
}

bool RocketLauncher::outOfAmmo() { return (ammo < 5); }

int RocketLauncher::getID(){
  return this->ID;
}
