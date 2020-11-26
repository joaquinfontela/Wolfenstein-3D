#include "../../../../includes/Model/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo) : ammo(newAmmo) {}

void Shootable::attack() { shoot(); }

bool Shootable::outOfAmmo() { return (ammo == 0); }