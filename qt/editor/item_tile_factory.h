#ifndef ITEM_TILE_FACTORY_H
#define ITEM_TILE_FACTORY_H

#include "tile.h"
#include "tile_factory.h"
#include <vector>

class item_tile_factory : public tile_factory
{
public:
    item_tile_factory();
    tile* get_tile(std::vector<int>& coordinates) override;
};

#endif // ITEM_TILE_FACTORY_H
