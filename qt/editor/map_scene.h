#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>

class map_scene : public QGraphicsScene
{
      Q_OBJECT
public:
    map_scene(QWidget *parent, int col, int row, int tile_size);
    void paint_grill(int col, int row, int tile_size);
};

#endif // MAP_SCENE_H
