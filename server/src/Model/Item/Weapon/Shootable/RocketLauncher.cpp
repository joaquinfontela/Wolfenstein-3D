#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

bool RocketLauncher::hasAmmo() { return (ammo < 5); }

int RocketLauncher::getID() { return this->ID; }
