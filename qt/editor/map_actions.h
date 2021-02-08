#ifndef MAP_ACTIONS_H
#define MAP_ACTIONS_H

#include <QObject>
#include "editor.h"
#include "map_scene.h"
#include <vector>
#include "ui_editor.h"

class map_actions : public QObject
{
    Editor* editor;
    map_scene* map;
public:
    map_actions(Editor* editor, map_scene* map_to_paint);
    bool eventFilter(QObject *obj, QEvent *event);
    void add_to_map(int x, int y);
    std::vector<int> get_coordinate(int x, int y);
};

#endif // MAP_ACTIONS_H
