#include <yaml-cpp/yaml.h>

#include <fstream>
#include <string>

#include "../Coordinate/Coordinate.h"

class YAMLMapWriter {
 private:
  std::string fileName;
  YAML::Node getData();

 public:
  YAMLMapWriter(std::string& fileName);
  void addCoordinateWhereObjectWithIdIsIn(int objectId, Coordinate& coordinate);
};