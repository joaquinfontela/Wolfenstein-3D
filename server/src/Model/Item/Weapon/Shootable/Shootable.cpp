#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo) : ammo(newAmmo) {}

Shootable::~Shootable() {}

unsigned int Shootable::attack() { return shoot(); }

bool Shootable::outOfAmmo() { return (ammo == 0); }