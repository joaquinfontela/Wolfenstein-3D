#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "../../../../../common/includes/YAML/YAMLConfigReader.h"
#include "Weapon.h"

class WeaponFactory {
 private:
  YAMLConfigReader yamlConfigReader;

 public:
  WeaponFactory();
  WeaponFactory(std::string& configFileName);
  Weapon* getWeapon(int weaponId, unsigned int weaponUniqueId);
};

#endif