#include "../../../../includes/Model/Item/Weapon/Weapon.h"

Weapon::~Weapon() {}

bool Weapon::canBePickedUpBy(Player& player) {
  // return !player.hasThisWeapon();
  return true;
}

void Weapon::pickUp(Player& player) { player.equipWeapon(*this); }