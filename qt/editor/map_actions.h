#ifndef MAP_ACTIONS_H
#define MAP_ACTIONS_H

#include <QObject>
#include "editor.h"
#include "my_map.h"
#include <vector>

class map_actions : public QObject
{
    Q_OBJECT

    Editor* editor;
    my_map& map;
public:
    map_actions(Editor* editor, my_map& map_to_paint);
    bool eventFilter(QObject *obj, QEvent *event);
    bool is_inside(int x, int y);
    void add_to_map(int x, int y);
    std::vector<int> get_coordinate(int x, int y);
};

#endif // MAP_ACTIONS_H
