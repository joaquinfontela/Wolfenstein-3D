#include "../../../../../includes/Model/Item/Weapon/Shootable/Minigun.h"

int Minigun::getID() { return this->ID; }

bool Minigun::hasAmmo() { return this->ammo > 0; }

int Minigun::getRange(){
  return INT_MAX - 1;
}

int Minigun::getUniqueId(){ return this->uniqueId;}
