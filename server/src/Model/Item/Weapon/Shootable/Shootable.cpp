#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo) : ammo(newAmmo) {}

Shootable::~Shootable() {}

unsigned int Shootable::shoot() {
  ammo--;
  return this->getRandomDamage();
}

bool Shootable::outOfAmmo() { return (ammo == 0); }