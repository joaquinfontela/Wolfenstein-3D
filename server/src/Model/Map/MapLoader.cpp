#include "../../../includes/Model/Map/MapLoader.h"

MapLoader::MapLoader(std::string& yamlFile) : yamlReader(yamlFile) {
  this->weaponIdStart = yamlReader.getWeaponsIdLimits().at(0);
  this->weaponIdEnd = yamlReader.getWeaponsIdLimits().at(1);
  this->itemIdStart = yamlReader.getItemsIdLimits().at(0);
  this->itemIdEnd = yamlReader.getItemsIdLimits().at(1);
  this->doorIdStart = yamlReader.getDoorsIdLimits().at(0);
  this->doorIdEnd = yamlReader.getDoorsIdLimits().at(1);
  this->wallIdStart = yamlReader.getWallsIdLimits().at(0);
  this->wallIdEnd = yamlReader.getWallsIdLimits().at(1);
  this->itemCoordinateMap = yamlReader.getItemCoordinateMap();
}

Map* MapLoader::loadMap() {
  std::vector<int> dimensions = yamlReader.getMapDimensions();
  Map* map = new Map(dimensions.at(0), dimensions.at(1));
  std::vector<Coordinate> respPoints = yamlReader.getRespawnLocations();
  map->setRespawnPoints(respPoints);
  this->addWeaponsToMap(map);
  this->addItemsToMap(map);
  this->addDoorsToMap(map);
  this->addWallsToMap(map);
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
      map->addWeaponDropAt(
          weaponFactory.getWeapon(currentId,
                                  Map::getAndIncreaseByOneNextUniqueItemId()),
          c.getX(), c.getY());
      // std::cout << "(" << c.getX() << ", " << c.getY() << "): " << currentId
      //        << std::endl;
    }
  }
}

void MapLoader::addItemsToMap(Map* map) {
  int currentId;
  ItemFactory itemFactory;
  for (currentId = this->itemIdStart; currentId <= itemIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId)) continue;
    std::vector<Coordinate> coordinatesWhereItemIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereItemIsIn) {
      map->addItemDropAt(
          itemFactory.getItem(currentId,
                              Map::getAndIncreaseByOneNextUniqueItemId()),
          c.getX(), c.getY());
      //  std::cout << "(" << c.getX() << ", " << c.getY() << "): " << currentId
      //              << std::endl;
    }
  }
}

void MapLoader::addDoorsToMap(Map* map) {
  int currentId;
  DoorFactory doorFactory;
  for (currentId = this->doorIdStart; currentId <= doorIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId)) continue;
    std::vector<Coordinate> coordinatesWhereDoorIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereDoorIsIn) {
      map->addDoorAt(doorFactory.getDoor(currentId), c.getX(), c.getY());
      //  std::cout << "(" << c.getX() << ", " << c.getY() << "): " << currentId
      //            << std::endl;
    }
  }
}

void MapLoader::addWallsToMap(Map* map) {
  int currentId;
  WallFactory wallFactory;
  for (currentId = this->wallIdStart; currentId <= wallIdEnd; currentId++) {
    if (!idIsInItemCoordinateMap(currentId)) continue;
    std::vector<Coordinate> coordinatesWhereWallIsIn =
        itemCoordinateMap.at(currentId);
    for (Coordinate c : coordinatesWhereWallIsIn) {
      map->addWallAt(wallFactory.getWall(currentId), c.getX(), c.getY());
    }
  }
}

bool MapLoader::idIsInItemCoordinateMap(int itemId) {
  return (itemCoordinateMap.find(itemId) != itemCoordinateMap.end());
}
