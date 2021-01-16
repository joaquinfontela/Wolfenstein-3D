#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include "tile.h"
#include <vector>

class tile_factory
{
public:
    virtual tile* get_tile(std::vector<int>& coordinates) = 0;
};

#endif // TILE_FACTORY_H
