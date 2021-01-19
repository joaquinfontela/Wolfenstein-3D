#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

bool RocketLauncher::hasAmmo() { return (ammo < 5); }

int RocketLauncher::getID() { return this->ID; }

int RocketLauncher::getRange(){
  return INT_MAX;
}

int RocketLauncher::getUniqueId(){ return this->uniqueId;}
