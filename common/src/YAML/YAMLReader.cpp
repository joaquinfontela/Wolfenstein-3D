#include "../../includes/YAML/YAMLReader.h"

#include <fstream>
#define FROM_ID 1
#define TO_ID 20

YAMLReader::YAMLReader(std::string& fileName) { this->fileName = fileName; }

YAML::Node YAMLReader::getData() { return YAML::LoadFile(this->fileName); }

std::vector<Coordinate> YAMLReader::getTileCoordinatesWhereObjectIsIn(
    int objectId) {
  YAML::Node data = this->getData();
  std::vector<Coordinate> coordinates;
  if (!data[objectId]) return coordinates;
  std::vector<std::vector<int>> coordinatesData =
      data[objectId].as<std::vector<std::vector<int>>>();
  for (std::vector<int> c : coordinatesData)
    coordinates.push_back(Coordinate(c));
  return coordinates;
}

std::map<int, std::vector<Coordinate>> YAMLReader::getItemCoordinateMap() {
  int i;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap;
  for (i = FROM_ID; i <= TO_ID; i++) {
    itemCoordinateMap[i] = this->getTileCoordinatesWhereObjectIsIn(i);
  }
  return itemCoordinateMap;
}

std::vector<int> YAMLReader::getMapDimensions() {
  YAML::Node data = this->getData();
  std::vector<int> dimensions;
  try {
    dimensions.push_back(data["dimx"].as<int>());
    dimensions.push_back(data["dimy"].as<int>());
  } catch (YAML::TypedKeyNotFound<std::string>& e) {
    std::cout << "Key not found: " << e.key << std::endl;
  }
  return dimensions;
}

std::vector<int> YAMLReader::getWeaponsIdLimits() {
  YAML::Node data = this->getData();
  std::vector<int> weaponsIdLimits;
  weaponsIdLimits.push_back(data["weapon id start"].as<int>());
  weaponsIdLimits.push_back(data["weapon id end"].as<int>());
  return weaponsIdLimits;
}

std::vector<int> YAMLReader::getItemsIdLimits() {
  YAML::Node data = this->getData();
  std::vector<int> itemsIdLimits;
  itemsIdLimits.push_back(data["item id start"].as<int>());
  itemsIdLimits.push_back(data["item id end"].as<int>());
  return itemsIdLimits;
}