#include <iostream>

#include "../../includes/YAML/YAMLReader.h"

int main() {
  YAMLReader yamlReader;
  std::vector<std::vector<int>> coordinates = yamlReader.getId1s();
  for (std::vector<int> coordinate : coordinates) {
    std::cout << "(" << coordinate[0] << ", " << coordinate[1] << ")"
              << std::endl;
  }
  return 0;
}