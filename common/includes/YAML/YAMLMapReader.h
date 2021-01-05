#include <yaml-cpp/yaml.h>

#include <iostream>
#include <map>
#include <string>

#include "../Coordinate/Coordinate.h"

// compile with flag -lyaml-cpp

class YAMLMapReader {
 private:
  std::string fileName;
  YAML::Node getData();
  std::vector<Coordinate> getTileCoordinatesWhereObjectIsIn(int objectId);

 public:
  YAMLMapReader(std::string& fileName);
  std::map<int, std::vector<Coordinate>> getItemCoordinateMap();
  std::vector<int> getMapDimensions();
  std::vector<int> getWeaponsIdLimits();
  std::vector<int> getItemsIdLimits();
  std::vector<int> getDoorsIdLimits();
  std::vector<int> getWallsIdLimits();
};