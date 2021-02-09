#include "../../includes/YAML/YAMLMapReader.h"

#include <fstream>

YAMLMapReader::YAMLMapReader(std::string& fileName) {
  this->fileName = fileName;
  this->data = this->getData();
}

YAML::Node YAMLMapReader::getData() { return YAML::LoadFile(this->fileName); }

std::vector<Coordinate>
YAMLMapReader::getCoordinateVectorFromVectorOfVectorsOfSizeTwo(
    std::vector<std::vector<int>>& coordinatesData) {
  std::vector<Coordinate> coordinates;
  for (std::vector<int> c : coordinatesData)
    coordinates.push_back(Coordinate(c));

  return coordinates;
}

std::vector<Coordinate> YAMLMapReader::getTileCoordinatesWhereObjectIsIn(
    int objectId) {
  if (!data[objectId]) {
    std::vector<Coordinate> v;
    return v;
  }
  std::vector<std::vector<int>> coordinatesData =
      data[objectId].as<std::vector<std::vector<int>>>();
  return this->getCoordinateVectorFromVectorOfVectorsOfSizeTwo(coordinatesData);
}

std::vector<Coordinate> YAMLMapReader::getRespawnLocations() {
  std::vector<std::vector<int>> coordinatesData =
      data["0"].as<std::vector<std::vector<int>>>();
  return this->getCoordinateVectorFromVectorOfVectorsOfSizeTwo(coordinatesData);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getPartialItemCoordinateMap(int FROM_ID, int TO_ID) {
  int i;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap;
  for (i = FROM_ID; i <= TO_ID; i++) {
    itemCoordinateMap[i] = this->getTileCoordinatesWhereObjectIsIn(i);
  }

  return itemCoordinateMap;
}

std::map<int, std::vector<Coordinate>> YAMLMapReader::getItemCoordinateMap() {
  int FROM_ID = 0;
  int TO_ID = this->getWallsIdLimits().at(1);
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getWallTypeCoordinateMap() {
  int FROM_ID = this->getWallsIdLimits().at(0);
  int TO_ID = this->getWallsIdLimits().at(1);
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::map<int, std::vector<Coordinate>>
YAMLMapReader::getItemTypeCoordinateMap() {
  int FROM_ID = this->getItemsIdLimits().at(0);
  int TO_ID = this->getItemsIdLimits().at(1);
  return this->getPartialItemCoordinateMap(FROM_ID, TO_ID);
}

std::vector<int> YAMLMapReader::getMapDimensions() {
  std::vector<int> dimensions;
  try {
    dimensions.push_back(data["dimx"].as<int>());
    dimensions.push_back(data["dimy"].as<int>());
  } catch (YAML::TypedKeyNotFound<std::string>& e) {
  }
  return dimensions;
}

std::vector<int> YAMLMapReader::getWeaponsIdLimits() {
  std::vector<int> weaponsIdLimits;
  weaponsIdLimits.push_back(data["weapon id start"].as<int>());
  weaponsIdLimits.push_back(data["weapon id end"].as<int>());
  return weaponsIdLimits;
}

std::vector<int> YAMLMapReader::getItemsIdLimits() {
  std::vector<int> itemsIdLimits;
  itemsIdLimits.push_back(data["item id start"].as<int>());
  itemsIdLimits.push_back(data["item id end"].as<int>());
  return itemsIdLimits;
}

std::vector<int> YAMLMapReader::getDoorsIdLimits() {
  std::vector<int> doorsIdLimits;
  doorsIdLimits.push_back(data["door id start"].as<int>());
  doorsIdLimits.push_back(data["door id end"].as<int>());
  return doorsIdLimits;
}

std::vector<int> YAMLMapReader::getWallsIdLimits() {
  std::vector<int> wallsIdLimits;
  wallsIdLimits.push_back(data["wall id start"].as<int>());
  wallsIdLimits.push_back(data["wall id end"].as<int>());
  return wallsIdLimits;
}
