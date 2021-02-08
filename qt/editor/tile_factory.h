#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <vector>

#include "../../common/includes/YAML/YAMLMapReader.h"
#include "PathFactory.h"
#include "tile_item.h"

class tile_factory {
 private:
  bool isDoor(int tileItemId, std::vector<int>& doorsIdsLimits);
  bool isWall(int tileItemId, std::vector<int>& wallsIdsLimits);

 public:
  /**
   * @brief get a pointer to a tile_item depending on the coordinates of the
   * click in the matrix.
   *
   * @param coordinates a vector representing a coordinate.
   * @return a dynamic pointer to a tile_item.
   */
  virtual tile_item* get_tile(std::vector<int>& coordinates) = 0;

  bool isCumulative(int tileItemId, YAMLMapReader& yamlMapReader);
};

#endif  // TILE_FACTORY_H
