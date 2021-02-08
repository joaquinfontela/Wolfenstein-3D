#ifndef MAP_CANVAS_H
#define MAP_CANVAS_H

#include <vector>
#include <QFrame>
#include "tile_item.h"


typedef std::vector<std::vector<std::vector<tile_item*>>> TileMatrix;

class map_canvas : public QFrame
{

public:
    map_canvas(int col, int row);
    map_canvas(TileMatrix* tile_matrix);
    ~map_canvas();
    bool paint_tile(std::vector<int> coordinates, tile_item* tile);
    std::vector<tile_item*> tiles_at_coordinates(std::vector<int> coordinates);
    void erase_tiles_at(std::vector<int> coordinates);

    TileMatrix grilla;
    int cant_col;
    int cant_row;
};

#endif // MAP_CANVAS_H
