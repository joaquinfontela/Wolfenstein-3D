#ifndef YAMLCONFIGREADER_H
#define YAMLCONFIGREADER_H

#include <yaml-cpp/yaml.h>

class YAMLConfigReader {
 private:
  std::string fileName;
  YAML::Node data;
  YAML::Node getData();

 public:
  YAMLConfigReader(std::string fileName);
  int getBulletAmountAtStart();
  int getBulletAmountDropWhenPlayerDies();
  int getMaxAmountOfBullets();
  int getBulletAmountWhenPickUpAmmo();
  int getMaxHealth();
  int getMaxReviveTimes();
  int getMaxHealthToBeAbleToPickUpBloodItem();
  int getHealthSumWhenPickingUpItem(int itemId);
  int getPointsSumWhenPickingUpItem(int itemId);
  std::vector<int> getMinAndMaxDamagePerBullet();
  int getBlastFrequency(int weaponId);
  int getShotsPerBlast(int weaponId);
  int ammoLostPerShot(int weaponId);
  int precision(int weaponId);
};

#endif