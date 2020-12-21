#include "../../includes/YAML/YAMLReader.h"

YAMLReader::YAMLReader() { this->fileName = "example.yaml"; }

YAML::Node YAMLReader::getData() { return YAML::LoadFile(this->fileName); }

std::string YAMLReader::getFirstName() {
  YAML::Node data = this->getData();
  return data["first-name"].as<std::string>();
}