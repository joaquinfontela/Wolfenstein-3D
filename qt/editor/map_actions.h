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
    my_map* map;

public:
    map_actions(Editor* editor, my_map* map);
    bool eventFilter(QObject *obj, QEvent *event);
    bool is_inside(int x, int y);
    void paint_map(std::vector<int> coordinates);
    void paint_big_tile(std::vector<int> position, tile* tile);
    void paint_multiple_tile(std::vector<int> position, std::vector<tile*> tiles);
    void erase_panting(std::vector<int> position);
    void add_to_map(int x, int y);
    std::vector<int> get_coordinate(int x, int y);
};

#endif // MAP_ACTIONS_H
