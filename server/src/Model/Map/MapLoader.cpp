#include "../../../includes/Model/Map/MapLoader.h"

MapLoader::MapLoader(std::string& yamlFile) : yamlReader(yamlFile) {
  std::cout<<"-9"<<std::endl;
  this->weaponIdStart = yamlReader.getWeaponsIdLimits().at(0);
  std::cout<<"-8"<<std::endl;
  this->weaponIdEnd = yamlReader.getWeaponsIdLimits().at(1);
  std::cout<<"-7"<<std::endl;
  this->itemIdStart = yamlReader.getItemsIdLimits().at(0);
  std::cout<<"-6"<<std::endl;
  this->itemIdEnd = yamlReader.getItemsIdLimits().at(1);
  std::cout<<"-5"<<std::endl;
  this->doorIdStart = yamlReader.getDoorsIdLimits().at(0);
  std::cout<<"-4"<<std::endl;
  this->doorIdEnd = yamlReader.getDoorsIdLimits().at(1);
  std::cout<<"-3"<<std::endl;
  this->wallIdStart = yamlReader.getWallsIdLimits().at(0);
  std::cout<<"-2"<<std::endl;
  this->wallIdEnd = yamlReader.getWallsIdLimits().at(1);
  std::cout<<"-1"<<std::endl;
  this->itemCoordinateMap = yamlReader.getItemCoordinateMap();
}

Map* MapLoader::loadMap() {
  std::cout<<"0"<<std::endl;
  std::vector<int> dimensions = yamlReader.getMapDimensions();
  Map* map = new Map(dimensions.at(0), dimensions.at(1));
    std::cout<<"1"<<std::endl;
  this->addWeaponsToMap(map);
    std::cout<<"2"<<std::endl;
  this->addItemsToMap(map);
    std::cout<<"3"<<std::endl;
  this->addDoorsToMap(map);
    std::cout<<"4"<<std::endl;
  this->addWallsToMap(map);
    std::cout<<"5"<<std::endl;
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
        std::cout << "(" << c.getX() << ", " << c.getY() << "): " << currentId
                << std::endl;
    }
  }
}

bool MapLoader::idIsInItemCoordinateMap(int itemId) {
  return (itemCoordinateMap.find(itemId) != itemCoordinateMap.end());
}
