#include "../../../includes/Model/Item/Ammo.h"

Ammo::Ammo() : Item() {}

Ammo::~Ammo() {}

bool Ammo::canBePickedUpBy(Player& player) {
  // return ! player.hasMaxAmmo();
  return true;
}

void Ammo::pickUp(Player& player) { player.pickUpAmmo(); }
