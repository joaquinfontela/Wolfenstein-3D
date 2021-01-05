#include "../../../includes/Model/Map/MapLoader.h"

MapLoader::MapLoader(std::string& yamlFile) : yamlReader(yamlFile) {
  this->weaponIdStart = yamlReader.getWeaponsIdLimits().at(0);
  this->weaponIdEnd = yamlReader.getWeaponsIdLimits().at(1);
  this->itemIdStart = yamlReader.getItemsIdLimits().at(0);
  this->itemIdEnd = yamlReader.getItemsIdLimits().at(1);
  this->itemCoordinateMap = yamlReader.getItemCoordinateMap();
}

Map* MapLoader::loadMap() {
  std::vector<int> dimensions = yamlReader.getMapDimensions();
  Map* map = new Map(dimensions.at(0), dimensions.at(1));
  this->addWeaponsToMap(map);
  this->addItemsToMap(map);
  return map;
}

void MapLoader::addWeaponsToMap(Map* map) {
  int currentId;
  WeaponFactory weaponFactory;
  for (currentId = this->weaponIdStart; currentId <= weaponIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId)) continue;
    std::vector<Coordinate> coordinatesWhereWeaponIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereWeaponIsIn) {
      map->addWeaponDropWithIdAt(weaponFactory.getWeapon(currentId), c.getX(),
                                 c.getY());
    }
  }
}

void MapLoader::addItemsToMap(Map* map) {
  int currentId;
  int currentItemUniqueId = 0;
  ItemFactory itemFactory;
  for (currentId = this->itemIdStart; currentId <= itemIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId)) continue;
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

bool MapLoader::idIsInItemCoordinateMap(int itemId) {
  return (itemCoordinateMap.find(itemId) != itemCoordinateMap.end());
}
