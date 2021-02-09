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

    /**
     * @param x an int that represents the x position of the mouse click.
     * @param y an int that represents the y position of the mouse click.
     * @return an int vector that represent the coordinates of the tileset.
     */
    std::vector<int> get_tile_coordinate(int x, int y);
    /**
     * @param x an int that represents the x position of the mouse click.
     * @param y an int that represents the y position of the mouse click.
     * @return a bolean that represent if the mouse click was in a tile zone.
     */
    bool is_inside(int x, int y);
    /**
     * @brief paint a grill in the scene.
     *
     * @param cant_row an int that represents the number of row in the grid.
     */
    void paint_grill(int cant_row);
public:
    /**
     * @brief create and return a tile_item that is asociated at the coordinates clicked
     * @param x an int that represents the x position of the mouse click.
     * @param y an int that represents the y position of the mouse click.
     * @return a pointer to a tile_item or NULL if the click was outside the tile zone.
     */
    tile_item* tile_clicked(int x, int y);
    /**
     * @brief reemplace the tileset of the scene for a new one created from the param passed.
     * @param path a QString that represent the path of the tileset image.
     * @param cant_row an int that represent the number of rows of the tileset.
     * @param factory an tile_factory that is asociated at the type of tiles that you want to create.
     */
    void update_tileset(QString path, int cant_row, tile_factory* factory);
    tiles_container(QString path, int cant_row, tile_factory* factory);
    tiles_container();
    ~tiles_container();
    bool is_empty();
};

#endif // TILES_CONTAINER_H
