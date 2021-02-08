#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <vector>

#include "PathFactory.h"
#include "tile_item.h"

class tile_factory {
 public:
  /**
   * @brief get a pointer to a tile_item depending on the coordinates of the
   * click in the matrix.
   *
   * @param coordinates a vector representing a coordinate.
   * @return a dynamic pointer to a tile_item.
   */
  virtual tile_item* get_tile(std::vector<int>& coordinates) = 0;
};

#endif  // TILE_FACTORY_H
