#include <yaml-cpp/yaml.h>

#include <iostream>
#include <string>

class YAMLReader {
 private:
  std::string fileName;
  YAML::Node getData();

 public:
  YAMLReader();
  std::string getFirstName();
};