#ifndef MAP_PAINTER_H
#define MAP_PAINTER_H

#include <vector>
#include "tile.h"
#include "my_map.h"
#include "map_canvas.h"

class Map_painter
{
private:
    int tile_size;
    my_map& map;
    std::vector<int> get_position(std::vector<int> coordinates);
    void paint_big_tile(std::vector<int> position, tile* tile);
    void paint_multiple_tile(std::vector<int> position, std::vector<tile*> tiles);
    void erase_panting(std::vector<int> position);
public:
    Map_painter(int tile_size, my_map& map_to_paint);
    void paint_map(std::vector<int> coordinates, std::vector<tile*> tiles);
    void paint_all_tiles(map_canvas* mc);
};

#endif // MAP_PAINTER_H
