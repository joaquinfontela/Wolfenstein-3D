#include "../../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"

int MachineGun::getID() { return this->ID; }

bool MachineGun::hasAmmo() { return this->ammo > 0; }

int MachineGun::getRange(){
  return INT_MAX - 1;
}

int MachineGun::getUniqueId(){ return this->uniqueId;}
