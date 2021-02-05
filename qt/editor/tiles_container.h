#ifndef TILES_CONTAINER_H
#define TILES_CONTAINER_H

#include <QGraphicsScene>
#include "tile_item.h"
#include "tile_factory.h"
#include <QGraphicsPixmapItem>

class tiles_container : public QGraphicsScene
{
    tile_factory* factory;
    int cant_rows;
    QGraphicsPixmapItem* pm_item;
    float margin_vertical;
    float margin_horizontal;
    QLabel* label;

    std::vector<int> get_tile_coordinate(int x, int y);
    bool is_inside(int x, int y);
    void paint_grill(int cant_row);

public:
    tile_item* tile_clicked(int x, int y);
    void update_tileset(QString path, int cant_row, tile_factory* factory);
    tiles_container(QString path, int cant_row, tile_factory* factory);
    tiles_container();
    bool is_empty();
};

#endif // TILES_CONTAINER_H
