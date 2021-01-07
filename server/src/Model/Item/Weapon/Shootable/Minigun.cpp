#include "../../../../../includes/Model/Item/Weapon/Shootable/Minigun.h"

unsigned int Minigun::attack() { return shoot(); }

int Minigun::getID(){
  return this->ID;
}

bool Minigun::hasAmmo(){ return this->ammo > 0;}
