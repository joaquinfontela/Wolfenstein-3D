#ifndef ITEM_TILE_FACTORY_H
#define ITEM_TILE_FACTORY_H

#include <vector>

#include "tile_item.h"
#include "tile_factory.h"

class item_tile_factory : public tile_factory {
 public:
  item_tile_factory();
  tile_item* get_tile(std::vector<int>& coordinates) override;
};

#endif  // ITEM_TILE_FACTORY_H
