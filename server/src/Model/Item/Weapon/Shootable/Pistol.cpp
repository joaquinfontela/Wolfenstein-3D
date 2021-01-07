#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

int Pistol::getID() { return this->ID; }

bool Pistol::hasAmmo() { return this->ammo > 0; }
