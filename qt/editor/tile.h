#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <QString>

class tile
{
    QLabel label;
    int type;
    QImage my_image;
    bool cumulative;
public:
    tile(QString path, int tipo, bool cumulative);
    QImage get_image();
    bool accept_tile(tile* tile);
};

#endif // TILE_H
