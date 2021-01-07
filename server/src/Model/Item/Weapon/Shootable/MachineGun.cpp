#include "../../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"

unsigned int MachineGun::attack() {
  unsigned int damage = 0;
  for (int i = 0; i < 5; i++) {
    damage += shoot();
  }
  return damage;
}

int MachineGun::getID(){
  return this->ID;
}
