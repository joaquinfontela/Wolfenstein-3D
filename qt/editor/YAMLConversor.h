#ifndef YAML_CONVERSOR_H
#define YAML_CONVERSOR_H

#include <QString>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "PathFactory.h"
#include "tile.h"

typedef std::vector<std::vector<std::vector<tile*>>> TileMatrix;

class YAMLConversor {
 private:
  std::string fileName;

 public:
  YAMLConversor(std::string& fileName) : fileName(fileName) {}
  void updateTileMatrix(TileMatrix& tileMatrix);
};

#endif