#include <yaml-cpp/yaml.h>

#include <iostream>
#include <map>
#include <string>

#include "../Coordinate/Coordinate.h"

// compile with flag -lyaml-cpp

class YAMLMapReader {
 private:
  std::string fileName;
  YAML::Node data;
  YAML::Node getData();
  std::map<int, std::vector<Coordinate>> getPartialItemCoordinateMap(
      int FROM_ID, int TO_ID);

 public:
  YAMLMapReader(std::string& fileName);
  std::vector<Coordinate> getTileCoordinatesWhereObjectIsIn(int objectId);
  std::map<int, std::vector<Coordinate>> getItemCoordinateMap();
  std::map<int, std::vector<Coordinate>> getWallTypeCoordinateMap();
  std::map<int, std::vector<Coordinate>> getItemTypeCoordinateMap();
  std::vector<int> getMapDimensions();
  std::vector<int> getWeaponsIdLimits();
  std::vector<int> getItemsIdLimits();
  std::vector<int> getDoorsIdLimits();
  std::vector<int> getWallsIdLimits();
};
