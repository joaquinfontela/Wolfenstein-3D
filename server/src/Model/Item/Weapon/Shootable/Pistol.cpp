#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

unsigned int Pistol::attack() { return shoot(); }

int Pistol::getID(){
  return this->ID;
}
