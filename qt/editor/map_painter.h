#ifndef MAP_PAINTER_H
#define MAP_PAINTER_H

#include <vector>
#include "tile_item.h"
#include "map_scene.h"
#include "map_canvas.h"

class Map_painter
{
private:
    int tile_size;
    map_scene* scene;
    map_canvas* mc;
    std::vector<int> get_position(std::vector<int> coordinates);
    void paint_big_tile(std::vector<int> position, tile_item* tile);
    void paint_multiple_tile(std::vector<int> position, std::vector<tile_item*> tiles);
    void erase_panting(std::vector<int> coordinates);
public:
    Map_painter(int tile_size, map_scene* map_to_paint, map_canvas* map_canvas);
    void paint_map(std::vector<int> coordinates, std::vector<tile_item*> tiles);
    void paint_all_tiles();
};

#endif // MAP_PAINTER_H
