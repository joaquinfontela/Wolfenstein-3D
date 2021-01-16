#ifndef MAP_CONTAINER_H
#define MAP_CONTAINER_H

#include <QWidget>

class map_container : public QWidget
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);
    map_container(int col, int row);
    virtual ~map_container() {}
};

#endif // MAP_CONTAINER_H
