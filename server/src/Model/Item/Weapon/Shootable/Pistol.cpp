#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

int Pistol::getID() { return this->ID; }

bool Pistol::hasAmmo() { return this->ammo > 0; }

int Pistol::getRange(){
  return INT_MAX - 1;
}

int Pistol::getUniqueId(){ return this->uniqueId;}
