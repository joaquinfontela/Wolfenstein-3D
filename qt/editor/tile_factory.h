#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <vector>

#include "PathFactory.h"
#include "tile_item.h"

class tile_factory {
 public:
  virtual tile_item* get_tile(std::vector<int>& coordinates) = 0;
};

#endif  // TILE_FACTORY_H
