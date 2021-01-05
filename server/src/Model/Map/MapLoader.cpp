#include "../../../includes/Model/Map/MapLoader.h"

MapLoader::MapLoader(int weaponIdStart, int weaponIdEnd, int itemIdStart,
                     int itemIdEnd) {
  this->weaponIdStart = weaponIdStart;
  this->weaponIdEnd = weaponIdEnd;
  this->itemIdStart = itemIdStart;
  this->itemIdEnd = itemIdEnd;
}

Map* MapLoader::loadMap(
    std::vector<int> dimensions,
    std::map<int, std::vector<Coordinate>> itemCoordinateMap) {
  Map* map = new Map(dimensions.at(0), dimensions.at(1));
  this->addWeaponsToMap(map, itemCoordinateMap);
  this->addItemsToMap(map, itemCoordinateMap);
  return map;
}

void MapLoader::addWeaponsToMap(
    Map* map, std::map<int, std::vector<Coordinate>> itemCoordinateMap) {
  int currentId;
  for (currentId = this->weaponIdStart; currentId <= weaponIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId, itemCoordinateMap)) continue;
    std::vector<Coordinate> coordinatesWhereWeaponIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereWeaponIsIn) {
      map->addWeaponDropWithIdAt(weaponFactory.getWeapon(currentId), c.getX(),
                                 c.getY());
    }
  }
}

void MapLoader::addItemsToMap(
    Map* map, std::map<int, std::vector<Coordinate>> itemCoordinateMap) {
  int currentId;
  int currentItemUniqueId = 0;
  for (currentId = this->itemIdStart; currentId <= itemIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId, itemCoordinateMap)) continue;
    currentItemUniqueId++;
    std::vector<Coordinate> coordinatesWhereItemIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereItemIsIn) {
      map->addItemDropWithIdAt(
          itemFactory.getItem(currentId, currentItemUniqueId), c.getX(),
          c.getY());
    }
  }
}

bool MapLoader::idIsInItemCoordinateMap(
    int itemId, std::map<int, std::vector<Coordinate>> itemCoordinateMap) {
  return (itemCoordinateMap.find(itemId) != itemCoordinateMap.end());
}
