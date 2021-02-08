#include "tile_factory.h"

tile_factory::tile_factory() {}

bool tile_factory::isCumulative(int tileItemId, YAMLMapReader& yamlMapReader) {
  std::vector<int> doorsIdLimits = yamlMapReader.getDoorsIdLimits();
  std::vector<int> wallsIdLimits = yamlMapReader.getWallsIdLimits();

  return !(this->isDoor(tileItemId, doorsIdLimits) ||
           this->isWall(tileItemId, wallsIdLimits));
}

bool tile_factory::isDoor(int tileItemId, std::vector<int>& doorsIdsLimits) {
  return (tileItemId >= doorsIdLimits.at(0) &&
          tileItemId <= doorsIdLimits.at(1));
}

bool tile_factory::isWall(int tileItemId, std::vector<int>& wallsIdsLimits) {
  return (tileItemId >= wallsIdLimits.at(0) &&
          tileItemId <= wallsIdLimits.at(1));
}