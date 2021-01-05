#include <yaml-cpp/yaml.h>

#include <fstream>
#include <string>

#include "../Coordinate/Coordinate.h"

class YAMLWriter {
 private:
  std::string fileName;
  YAML::Node getData();

 public:
  YAMLWriter(std::string& fileName);
  void addCoordinateWhereObjectWithIdIsIn(int objectId, Coordinate& coordinate);
};