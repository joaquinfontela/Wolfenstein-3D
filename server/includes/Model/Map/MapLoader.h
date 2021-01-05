#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <map>
#include <vector>

#include "../../../../common/includes/Coordinate/Coordinate.h"
#include "../../../../common/includes/YAML/YAMLMapReader.h"
#include "../../../includes/Model/Item/ItemFactory.h"
#include "../../../includes/Model/Item/Weapon/WeaponFactory.h"
#include "Map.h"

class MapLoader {
 private:
  YAMLMapReader yamlReader;
  unsigned int weaponIdStart;
  unsigned int weaponIdEnd;
  unsigned int itemIdStart;
  unsigned int itemIdEnd;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap;
  void addWeaponsToMap(Map* map);
  void addItemsToMap(Map* map);
  bool idIsInItemCoordinateMap(int itemId);

 public:
  MapLoader(std::string& yamlFile);
  Map* loadMap();
};

#endif