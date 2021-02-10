#include "YAMLConversor.h"
#include "../../common/includes/YAML/YAMLMapReader.h"

#include "tile_factory.h"

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
      std::string path(pathFactory.getTilePath(id).c_str());
      tile_item* t = new tile_item(
          path, id, tile_factory::isCumulative(id, yamlMapReader));
      tileMatrix->at(c.getY() - 1)[c.getX() - 1].push_back(t);
    }
  }
  return tileMatrix;
}

TileMatrix* YAMLConversor::createEmptyMatrix(std::vector<int> mapDimensions) {
  int dimx = mapDimensions[0];
  int dimy = mapDimensions[1];
  TileMatrix* tileMatrix = new TileMatrix();
  for (int y = 0; y < dimy; y++) {
    std::vector<std::vector<tile_item*>> row;
    for (int x = 0; x < dimx; x++) {
      std::vector<tile_item*> column;
      row.push_back(column);
    }
    tileMatrix->push_back(row);
  }
  return tileMatrix;
}
