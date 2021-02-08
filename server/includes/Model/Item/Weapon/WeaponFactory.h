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

  /*
   * @brief [SERVER-SIDE] Receives an weaponId and returns the corresponding
   * weapon with id weaponUniqueId.
   *
   * @param weaponId integer that represents a weapon type.
   *
   * @param weaponUniqueId integer that differentiates a weapon from any other
   * one.
   *
   * @return a dynamic pointer to a weapon if weaponId is valid, nullptr
   * otherwise.
   */
  Weapon* getWeapon(int weaponId, unsigned int weaponUniqueId);
};

#endif