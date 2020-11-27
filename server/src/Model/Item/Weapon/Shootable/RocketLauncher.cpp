#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

RocketLauncher::RocketLauncher(int newAmmo) : Shootable(newAmmo) {}

void RocketLauncher::shoot() { ammo -= 5; }

bool RocketLauncher::outOfAmmo() { return (ammo < 5); }