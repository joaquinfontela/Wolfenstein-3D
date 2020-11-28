#include "../../../includes/Model/Item/Ammo.h"

Ammo::Ammo() : Item() {}

Ammo::~Ammo() {}

void Ammo::pickUp(Player& player) { player.pickUpAmmo(); }