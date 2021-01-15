#include "../../includes/YAML/YAMLMapReader.h"

#include <fstream>

YAMLMapReader::YAMLMapReader(std::string& fileName) {
  std::cout << 10 << std::endl;

  this->fileName = fileName;
  this->data = this->getData();
  std::cout << "Paso el getData" << std::endl;
}

YAML::Node YAMLMapReader::getData() { return YAML::LoadFile(this->fileName); }

std::vector<Coordinate>
YAMLMapReader::getCoordinateVectorFromVectorOfVectorsOfSizeTwo(
    std::vector<std::vector<int>>& coordinatesData) {
  std::cout << 11 << std::endl;

  std::vector<Coordinate> coordinates;
  for (std::vector<int> c : coordinatesData)
    coordinates.push_back(Coordinate(c));

  std::cout << "Paso el getTileCoordinates" << std::endl;
  return coordinates;
}

std::vector<Coordinate> YAMLMapReader::getTileCoordinatesWhereObjectIsIn(
    int objectId) {
  std::cout << 12 << std::endl;

  if (!data[objectId]) {
    std::vector<Coordinate> v;
    return v;
  }
  std::vector<std::vector<int>> coordinatesData =
      data[objectId].as<std::vector<std::vector<int>>>();
  return this->getCoordinateVectorFromVectorOfVectorsOfSizeTwo(coordinatesData);
}

std::vector<Coordinate> YAMLMapReader::getRespawnLocations() {
  std::cout << 13 << std::endl;

  std::vector<std::vector<int>> coordinatesData =
      data["respawn locations"].as<std::vector<std::vector<int>>>();
  return this->getCoordinateVectorFromVectorOfVectorsOfSizeTwo(coordinatesData);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getPartialItemCoordinateMap(int FROM_ID, int TO_ID) {
  std::cout << 14 << std::endl;

  int i;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap;
  for (i = FROM_ID; i <= TO_ID; i++) {
    itemCoordinateMap[i] = this->getTileCoordinatesWhereObjectIsIn(i);
  }

  return itemCoordinateMap;
}

std::map<int, std::vector<Coordinate>> YAMLMapReader::getItemCoordinateMap() {
  std::cout << 15 << std::endl;

  int FROM_ID = this->getWeaponsIdLimits().at(0);
  int TO_ID = this->getWallsIdLimits().at(1);
  std::cout << "Paso el getItemCoordinates" << std::endl;
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getWallTypeCoordinateMap() {
  std::cout << 16 << std::endl;

  int FROM_ID = this->getWallsIdLimits().at(0);
  int TO_ID = this->getWallsIdLimits().at(1);
  std::cout << "Paso el getWallTypeCoordinates" << std::endl;
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getItemTypeCoordinateMap() {
  std::cout << 17 << std::endl;

  int FROM_ID = this->getItemsIdLimits().at(0);
  int TO_ID = this->getItemsIdLimits().at(1);
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::vector<int> YAMLMapReader::getMapDimensions() {
  std::cout << 18 << std::endl;

  std::vector<int> dimensions;
  try {
    dimensions.push_back(data["dimx"].as<int>());
    dimensions.push_back(data["dimy"].as<int>());
    std::cout << "Paso el agarrar las dimensiones" << std::endl;
  } catch (YAML::TypedKeyNotFound<std::string>& e) {
    std::cout << "Key not found: " << e.key << std::endl;
  }
  return dimensions;
}

std::vector<int> YAMLMapReader::getWeaponsIdLimits() {
  std::cout << 19 << std::endl;

  std::vector<int> weaponsIdLimits;
  weaponsIdLimits.push_back(data["weapon id start"].as<int>());
  weaponsIdLimits.push_back(data["weapon id end"].as<int>());
  return weaponsIdLimits;
}

std::vector<int> YAMLMapReader::getItemsIdLimits() {
  std::cout << 2 << std::endl;

  std::vector<int> itemsIdLimits;
  itemsIdLimits.push_back(data["item id start"].as<int>());
  itemsIdLimits.push_back(data["item id end"].as<int>());
  return itemsIdLimits;
}

std::vector<int> YAMLMapReader::getDoorsIdLimits() {
  std::cout << 3 << std::endl;

  std::vector<int> doorsIdLimits;
  doorsIdLimits.push_back(data["door id start"].as<int>());
  doorsIdLimits.push_back(data["door id end"].as<int>());
  return doorsIdLimits;
}

std::vector<int> YAMLMapReader::getWallsIdLimits() {
  std::cout << 4 << std::endl;
  std::vector<int> wallsIdLimits;
  wallsIdLimits.push_back(data["wall id start"].as<int>());
  wallsIdLimits.push_back(data["wall id end"].as<int>());
  return wallsIdLimits;
}
