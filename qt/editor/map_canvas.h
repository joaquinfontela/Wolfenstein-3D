#ifndef MAP_CANVAS_H
#define MAP_CANVAS_H

#include <vector>
#include <QFrame>
#include "tile.h"


typedef std::vector<std::vector<std::vector<tile*>>> TileMatrix;

class map_canvas : public QFrame
{

public:
    map_canvas(int col, int row);
    map_canvas(TileMatrix* tile_matrix);
    bool paint_tile(std::vector<int> coordinates, tile* tile);
    std::vector<tile*> tiles_at_coordinates(std::vector<int> coordinates);

    TileMatrix grilla;
    int cant_col;
    int cant_row;
};

#endif // MAP_CANVAS_H
