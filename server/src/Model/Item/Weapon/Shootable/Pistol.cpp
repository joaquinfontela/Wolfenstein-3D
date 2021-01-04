#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

Pistol::Pistol(unsigned int ammo) : Shootable(ammo) {}

unsigned int Pistol::attack() {
  ammo--;
  return 1;
}