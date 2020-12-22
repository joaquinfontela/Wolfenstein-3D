#include "../../includes/YAML/YAMLReader.h"

YAMLReader::YAMLReader() { this->fileName = "example.yaml"; }

YAML::Node YAMLReader::getData() { return YAML::LoadFile(this->fileName); }

std::vector<std::vector<int>> YAMLReader::getId(int id) {
  YAML::Node data = this->getData();
  std::vector<std::vector<int>> coordinates =
      data[id].as<std::vector<std::vector<int>>>();
  return coordinates;
}

std::vector<std::vector<int>> YAMLReader::getId1s() { return getId(1); }