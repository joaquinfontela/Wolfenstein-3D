#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <map>
#include <vector>

#include "../../../../common/includes/Coordinate/Coordinate.h"
#include "../../../includes/Model/Item/ItemFactory.h"
#include "../../../includes/Model/Item/Weapon/WeaponFactory.h"
#include "Map.h"

class MapLoader {
 private:
  unsigned int weaponIdStart;
  unsigned int weaponIdEnd;
  unsigned int itemIdStart;
  unsigned int itemIdEnd;
  ItemFactory itemFactory;
  WeaponFactory weaponFactory;
  bool idIsInItemCoordinateMap(
      int itemId, std::map<int, std::vector<Coordinate>> itemCoordinateMap);
  void addWeaponsToMap(
      Map* map, std::map<int, std::vector<Coordinate>> itemCoordinateMap);
  void addItemsToMap(Map* map,
                     std::map<int, std::vector<Coordinate>> itemCoordinateMap);

 public:
  MapLoader(int weaponIdStart, int weaponIdEnd, int itemIdStart, int itemIdEnd);
  Map* loadMap(std::vector<int> dimensions,
               std::map<int, std::vector<Coordinate>> itemCoordinateMap);
};

#endif