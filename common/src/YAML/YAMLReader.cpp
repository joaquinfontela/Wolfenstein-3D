#include "../../includes/YAML/YAMLReader.h"
#define FROM_ID 1
#define TO_ID 20

YAMLReader::YAMLReader() { this->fileName = "example.yaml"; }

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