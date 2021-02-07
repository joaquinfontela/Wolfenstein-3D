#ifndef MAP_SAVE_H
#define MAP_SAVE_H

#include "QPushButton"
#include "open_window.h"
#include "tile_item.h"
#include "QListWidgetItem"

class map_save : public QPushButton
{
    

    std::vector<std::vector<std::vector<tile_item*>>> map;
    open_window* my_window;
    std::string map_name;

private slots:
    void set_map();

public:
    map_save(open_window* my_window, std::string map);
};

#endif // MAP_SAVE_H
