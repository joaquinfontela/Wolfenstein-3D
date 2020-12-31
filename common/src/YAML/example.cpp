#include <iostream>

#include "../../includes/Map/Map.h"
#include "../../includes/YAML/YAMLReader.h"

int main() {
  YAMLReader yamlReader;
  std::map<int, std::vector<Coordinate>> itemCoordinateMap =
      yamlReader.getItemCoordinateMap();
  Map tileMap(24, 24);
  for (auto item : itemCoordinateMap) {
    int itemId = item.first;
    std::vector<Coordinate> coordinates = item.second;
    for (Coordinate c : coordinates) {
      tileMap.addDropWithIdAt(itemId, c.getX(), c.getY());
    }
  }
  std::vector<int> dropIds = tileMap.getDropIdsAt(4, 2);
  for (int dropId : dropIds) {
    std::cout << dropId << std::endl;
  }
  return 0;
}