#include "YAMLConversor.h"

void YAMLConversor::updateTileMatrix(TileMatrix& tileMatrix) {
  YAMLMapReader yamlMapReader(this->fileName);
  std::map<int, std::vector<Coordinate>> itemCoordinateMap =
      yamlMapReader.getItemCoordinateMap();
  for (auto itemId : itemCoordinateMap) {
    int id = itemId.first;
    std::vector<Coordinate> coordinates = itemId.second;
    PathFactory pathFactory;
    for (Coordinate c : coordinates) {
      QString path(pathFactory.getTilePath(id).c_str());
      tile* t = new tile(path, id, false);  // provisory
      tileMatrix[c.getY() - 1][c.getX() - 1].push_back(t);
    }
  }
}