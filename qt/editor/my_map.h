#ifndef MY_MAP_H
#define MY_MAP_H

#include <QLabel>
#include <QPixmap>
#include <vector>
#include "tile.h"

class my_map : public QLabel
{
    QPixmap* my_pm;
public:
    tile* tile_to_paint;
    int tiles_to_paint;
    my_map(int col, int row, int tile_size);
    void paint_grill(int col, int row, int tile_size);
    void paintEvent(QPaintEvent *event) override;
    virtual ~my_map() {};
};

#endif // MY_MAP_H
