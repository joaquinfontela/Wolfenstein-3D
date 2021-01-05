#include "../../../../includes/Model/Item/Weapon/WeaponFactory.h"

#define DEFAULT_AMMO 0

#include "../../../../includes/Model/Item/Weapon/Knife.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/Minigun.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

Weapon* WeaponFactory::getWeapon(int weaponId) {
  switch (weaponId) {
    case 1:
      return new Knife();
      break;

    case 2:
      return new Pistol(DEFAULT_AMMO);
      break;

    case 3:
      return new MachineGun(DEFAULT_AMMO);
      break;

    case 4:
      return new Minigun(DEFAULT_AMMO);
      break;

    case 5:
      return new RocketLauncher(DEFAULT_AMMO);
      break;

    default:
      return nullptr;
      break;
  }
}