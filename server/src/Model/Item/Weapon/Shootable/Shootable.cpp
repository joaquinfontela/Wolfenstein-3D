#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo) : ammo(newAmmo) {}

Shootable::~Shootable() {}

unsigned int Shootable::shoot() {
  ammo--;
  return 1;  // random 1-10
}

bool Shootable::outOfAmmo() { return (ammo == 0); }