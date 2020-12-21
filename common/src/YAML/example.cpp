#include <iostream>

#include "../../includes/YAML/YAMLReader.h"
// compile with flag -lyaml-cpp

int main() {
  YAMLReader yamlReader;
  std::cout << yamlReader.getFirstName() << std::endl;
  return 0;
}