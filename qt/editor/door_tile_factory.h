#ifndef DOOR_TILE_FACTORY_H
#define DOOR_TILE_FACTORY_H

#include "tile_item.h"
#include "tile_factory.h"
#include <vector>

class door_tile_factory : public tile_factory
{
public:
    door_tile_factory();
    tile_item* get_tile(std::vector<int>& coordinates) override;
};

#endif // DOOR_TILE_FACTORY_H
