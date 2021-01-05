#include "../../includes/YAML/YAMLWriter.h"

YAMLWriter::YAMLWriter(std::string& fileName) { this->fileName = fileName; }

YAML::Node YAMLWriter::getData() { return YAML::LoadFile(this->fileName); }

void YAMLWriter::addCoordinateWhereObjectWithIdIsIn(int objectId,
                                                    Coordinate& coordinate) {
  YAML::Node data = this->getData();
  std::vector<std::vector<int>> coordinateVector;
  if (!data[objectId]) {
    coordinateVector.push_back(coordinate.getVector());
    data[objectId] = coordinateVector;
  } else {
    coordinateVector = data[objectId].as<std::vector<std::vector<int>>>();
    coordinateVector.push_back(coordinate.getVector());
    data[objectId] = coordinateVector;
  }
  YAML::Emitter emitter;
  emitter << data;
  std::ofstream yamlFile(this->fileName);
  yamlFile << emitter.c_str();
}