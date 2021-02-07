#ifndef FAKE_WALL_TILE_FACTORY_H
#define FAKE_WALL_TILE_FACTORY_H

#include <vector>

#include "PathFactory.h"
#include "tile_item.h"
#include "tile_factory.h"

class fake_wall_tile_factory : public tile_factory
{
public:
    fake_wall_tile_factory();
    tile_item* get_tile(std::vector<int>& coordinates) override;
};

#endif // FAKE_WALL_TILE_FACTORY_H
