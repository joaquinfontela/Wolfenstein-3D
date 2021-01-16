#ifndef TILESET_H
#define TILESET_H

#include <QPixmap>
#include <QImage>
#include <QLabel>

class tileset
{
    QPixmap pm;
public:
    tileset(QImage template_image, int col, int row);
    void copy_to_label(QLabel* label);
};

#endif // TILESET_H
