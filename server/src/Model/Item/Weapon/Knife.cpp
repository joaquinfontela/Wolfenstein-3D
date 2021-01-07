#include "../../../../includes/Model/Item/Weapon/Knife.h"

unsigned int Knife::attack() { return this->getRandomDamage(); }

int Knife::getID(){
  return this->ID;
}
