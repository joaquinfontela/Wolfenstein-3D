#ifndef DECORATION_TILE_FACTORY_H
#define DECORATION_TILE_FACTORY_H

#include <vector>

#include "tile_factory.h"
#include "tile_item.h"

class decoration_tile_factory : public tile_factory {
 public:
  decoration_tile_factory();
  tile_item* get_tile(std::vector<int>& coordinates) override;
};

#endif  // DECORATION_TILE_FACTORY_H
