#ifndef WALL_TILE_FACTORY_H
#define WALL_TILE_FACTORY_H

#include <vector>

#include "PathFactory.h"
#include "tile.h"
#include "tile_factory.h"

class wall_tile_factory : public tile_factory {
 public:
  wall_tile_factory();
  tile* get_tile(std::vector<int>& coordinates) override;
};

#endif  // WALL_TILE_FACTORY_H
