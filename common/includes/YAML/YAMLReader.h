#include <yaml-cpp/yaml.h>

#include <iostream>
#include <map>
#include <string>

#include "../Coordinate/Coordinate.h"

// compile with flag -lyaml-cpp

class YAMLReader {
 private:
  std::string fileName;
  YAML::Node getData();
  std::vector<Coordinate> getTileCoordinatesWhereObjectIsIn(int objectId);

 public:
  YAMLReader();
  std::map<int, std::vector<Coordinate>> getItemCoordinateMap();
  std::vector<int> getMapDimensions();
};