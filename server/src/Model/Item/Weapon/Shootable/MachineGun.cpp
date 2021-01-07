#include "../../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"

int MachineGun::getID() { return this->ID; }

bool MachineGun::hasAmmo() { return this->ammo > 0; }
