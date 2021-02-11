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

  // @return the health that gets the player when he picks up the item with id
  // itemId.
  // @param itemId represents an item type.
  int getHealthSumWhenPickingUpItem(int itemId);

  // @return the points that will be added to the score of the player when he
  // picks up the item with id itemId.
  // @param represents an item type.
  int getPointsSumWhenPickingUpItem(int itemId);
  std::vector<int> getMinAndMaxDamagePerBullet();
  int getPointsPerKill();

  // @param weaponId represents a weapon type.
  float getBlastFrequency(int weaponId);
  // @param weaponId represents a weapon type.
  int getShotsPerBlast(int weaponId);
  // @param weaponId represents a weapon type.
  int ammoLostPerShot(int weaponId);
  // @param weaponId represents a weapon type.
  float precision(int weaponId);

  float getMatchLength();
};

#endif
