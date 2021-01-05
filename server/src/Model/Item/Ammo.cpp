#include "../../../includes/Model/Item/Ammo.h"

Ammo::Ammo() : Item() {}

Ammo::~Ammo() {}

bool Ammo::canBePickedUpBy(Player* p) { return !p->hasMaxAmmo(); }

void Ammo::pickUp(Player* p) { p->pickUpAmmo(); }