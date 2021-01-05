#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "Weapon.h"

class WeaponFactory {
 public:
  Weapon* getWeapon(int weaponId);
};

#endif