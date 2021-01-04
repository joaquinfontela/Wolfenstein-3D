#include "../../../includes/Model/Item/Pistol.h"

Pistol::Pistol(unsigned int ammo) : Weapon(ammo) {}

unsigned int Pistol::attack() {
  ammo--;
  return 1;
}

bool Pistol::outOfAmmo() { return (ammo == 0); }
