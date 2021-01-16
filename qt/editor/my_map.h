#ifndef MY_MAP_H
#define MY_MAP_H

#include <QLabel>
#include <vector>
#include "tile.h"
#include "editor.h"

class my_map : public QLabel
{
    Editor* editor;

public:

    bool print_tile;
    my_map(int col, int row, Editor* editor);
    void paintEvent(QPaintEvent *event) override;
    virtual ~my_map() {};
};

#endif // MY_MAP_H
