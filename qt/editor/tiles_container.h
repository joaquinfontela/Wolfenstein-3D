#ifndef TILES_CONTAINER_H
#define TILES_CONTAINER_H

#include <QHBoxLayout>
#include "tile.h"
#include "tile_factory.h"

class tiles_container : public QHBoxLayout
{
    tile_factory* factory;
    int cant_rows;
    QLabel* label;

    std::vector<int> get_tile_coordinate(int x, int y);
    bool is_inside(int x, int y);
public:
    tile* tile_clicked(int x, int y);
    tiles_container(QString path, int cant_row, int height, tile_factory* factory);
};

#endif // TILES_CONTAINER_H
