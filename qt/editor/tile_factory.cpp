#include "tile_factory.h"

bool tile_factory::isCumulative(int tileItemId, YAMLMapReader& yamlMapReader) {
  std::vector<int> doorsIdsLimits = yamlMapReader.getDoorsIdLimits();
  std::vector<int> wallsIdsLimits = yamlMapReader.getWallsIdLimits();

  return !(tile_factory::isDoor(tileItemId, doorsIdsLimits) ||
           tile_factory::isWall(tileItemId, wallsIdsLimits));
}

bool tile_factory::isDoor(int tileItemId, std::vector<int>& doorsIdsLimits) {
  return (tileItemId >= doorsIdsLimits.at(0) &&
          tileItemId <= doorsIdsLimits.at(1));
}

bool tile_factory::isWall(int tileItemId, std::vector<int>& wallsIdsLimits) {
  return (tileItemId >= wallsIdsLimits.at(0) &&
          tileItemId <= wallsIdsLimits.at(1));
}
