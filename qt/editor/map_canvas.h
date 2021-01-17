#ifndef MAP_CANVAS_H
#define MAP_CANVAS_H

#include <vector>
#include <QFrame>
#include "tile.h"

class map_canvas : public QFrame
{
    std::vector<std::vector<std::vector<tile*>>> grilla;
public:
    map_canvas(int col, int row);
    bool paint_tile(std::vector<int> coordinates, tile* tile);
    std::vector<tile*> tiles_at_coordinates(std::vector<int> coordinates);

    int cant_col;
    int cant_row;
};

#endif // MAP_CANVAS_H
