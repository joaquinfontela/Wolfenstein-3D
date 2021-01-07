#include "../../../../includes/Model/Item/Weapon/WeaponFactory.h"

#define DEFAULT_AMMO 0

#include "../../../../includes/Model/Item/Weapon/Knife.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/Minigun.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"
#include "../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

WeaponFactory::WeaponFactory()
    : yamlConfigReader(std::string("common/src/YAML/config.yaml")) {}

WeaponFactory::WeaponFactory(std::string& configFileName)
    : yamlConfigReader(configFileName) {}

Weapon* WeaponFactory::getWeapon(int weaponId) {
  unsigned int minDamagePerBullet =
      yamlConfigReader.getMinAndMaxDamagePerBullet().at(0);
  unsigned int maxDamagePerBullet =
      yamlConfigReader.getMinAndMaxDamagePerBullet().at(1);
  unsigned int shotsPerBlast, ammoLostPerShot;
  if (weaponId != 1) {
    shotsPerBlast = yamlConfigReader.getShotsPerBlast(weaponId);
    ammoLostPerShot = yamlConfigReader.ammoLostPerShot(weaponId);
  }

  switch (weaponId) {
    case 1:
      return new Knife(minDamagePerBullet, maxDamagePerBullet);
      break;

    case 2:
      return new Pistol(DEFAULT_AMMO, minDamagePerBullet, maxDamagePerBullet,
                        shotsPerBlast, ammoLostPerShot,
                        yamlConfigReader.precision(2));
      break;

    case 3:
      return new MachineGun(DEFAULT_AMMO, minDamagePerBullet,
                            maxDamagePerBullet, shotsPerBlast, ammoLostPerShot,
                            yamlConfigReader.precision(3),
                            yamlConfigReader.getBlastFrequency(3));
      break;

    case 4:
      return new Minigun(DEFAULT_AMMO, minDamagePerBullet, maxDamagePerBullet,
                         shotsPerBlast, ammoLostPerShot,
                         yamlConfigReader.precision(4),
                         yamlConfigReader.getBlastFrequency(4));
      break;

    case 5:
      return new RocketLauncher(DEFAULT_AMMO, minDamagePerBullet,
                                maxDamagePerBullet, shotsPerBlast,
                                ammoLostPerShot);
      break;

    default:
      return nullptr;
      break;
  }
}