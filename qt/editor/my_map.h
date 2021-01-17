#ifndef MY_MAP_H
#define MY_MAP_H

#include <QLabel>
#include <vector>
#include "tile.h"
#include "editor.h"

class my_map : public QLabel
{

public:
    tile* tile_to_paint;
    int tiles_to_paint;
    my_map(int col, int row);
    void paintEvent(QPaintEvent *event) override;
    virtual ~my_map() {};
};

#endif // MY_MAP_H
