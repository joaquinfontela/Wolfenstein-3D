#include "YAMLConversor.h"

TileMatrix* YAMLConversor::updateTileMatrix() {
  YAMLMapReader yamlMapReader(this->fileName);
  TileMatrix* tileMatrix =
      this->createEmptyMatrix(yamlMapReader.getMapDimensions());
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

TileMatrix* YAMLConversor::createEmptyMatrix(std::vector<int> mapDimensions) {
  int dimx = mapDimensions[0];
  int dimy = mapDimensions[1];
  TileMatrix tileMatrix = new TileMatrix();
  for (int y = 0; y < dimy; y++) {
    std::vector<std::vector<tile*>> row;
    for (int x = 0; x < dimx; x++) {
      std::vector<tile*> column;
      row.push_back(column);
    }
    tileMatrix.push_back(row);
  }
  return tileMatrix;
}