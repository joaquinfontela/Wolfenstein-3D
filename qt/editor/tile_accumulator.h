#ifndef TILE_ACCUMULATOR_H
#define TILE_ACCUMULATOR_H

#include "not_cumulative_tile.h"
#include "cumulative_tile.h"
#include "tile.h"
#include <list>

class tile_accumulator : public not_cumulative_tile
{
    std::list<int> inside_tiles_types;
public:
    tile_accumulator();
};

#endif // TILE_ACCUMULATOR_H
