#ifndef TILE_CONTAINER_H
#define TILE_CONTAINER_H

#include "tile.h"
#include "tileset.h"
#include "QHBoxLayout"


class tile_container : QFrame
{
    QHBoxLayout* container;
    QLabel* image;
public:
    tile_container();
    void set_tileset(tileset ts);
};

#endif // TILE_CONTAINER_H
