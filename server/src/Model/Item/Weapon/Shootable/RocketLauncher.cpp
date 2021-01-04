#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

unsigned int RocketLauncher::attack() {
  unsigned int DAMAGE = 50;  // provisorio
  ammo -= 5;
  return DAMAGE;
}

bool RocketLauncher::outOfAmmo() { return (ammo < 5); }