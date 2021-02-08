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

  // Returns the health that gets the player when he picks up the item with id
  // itemId.
  int getHealthSumWhenPickingUpItem(int itemId);

  // Returns the points that will be added to the score of the player when he
  // picks up the item with id itemId.
  int getPointsSumWhenPickingUpItem(int itemId);
  std::vector<int> getMinAndMaxDamagePerBullet();
  int getPointsPerKill();
  float getBlastFrequency(int weaponId);
  int getShotsPerBlast(int weaponId);
  int ammoLostPerShot(int weaponId);
  float precision(int weaponId);
};

#endif
