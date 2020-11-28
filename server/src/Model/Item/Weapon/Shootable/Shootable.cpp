#include "../../../../../includes/Model/Item/Weapon/Shootable/Shootable.h"

Shootable::Shootable(int newAmmo) : ammo(newAmmo) {}

Shootable::~Shootable() {}

void Shootable::attack() { shoot(); }

bool Shootable::outOfAmmo() { return (ammo == 0); }