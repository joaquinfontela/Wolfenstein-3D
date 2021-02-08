#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>

class map_scene : public QGraphicsScene
{
      Q_OBJECT
public:
    map_scene(QWidget *parent, int col, int row, int tile_size);
    map_scene(QWidget* parent);
    /**
     * @brief paint a grill in the scene.
     *
     * @param col an int that represents the number of columns in the grid.
     * @param row an int that represents the number of row in the grid.
     * @param tile_size an int that represents the side size of the each square of the grid.
     */
    void paint_grill(int col, int row, int tile_size);
};

#endif // MAP_SCENE_H
