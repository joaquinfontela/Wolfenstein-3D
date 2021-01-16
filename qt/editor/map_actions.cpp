#include "map_actions.h"
#include "QEvent"
#include "QCursor"
#include "tile.h"
#include <iostream>
#include <QMouseEvent>
#include <iostream>
#include <QPainter>
#include "my_map.h"

#define MARGIN 7
#define SIDE_SIZE 40

map_actions::map_actions(Editor* editor, my_map* map)
{
    this->editor = editor;
    this->map = map;
}


bool map_actions::eventFilter(QObject *obj, QEvent *event){
        if (event->type() == QEvent::MouseButtonPress) {
           QMouseEvent* me = (QMouseEvent*)event;
           int x = me->localPos().x();
           int y = me->localPos().y();
           paint_map(x,y);
           return true;
        } else{
            return QObject::eventFilter(obj, event);
        }
}

bool map_actions::is_inside(int x, int y){

    int WIDTH = SIDE_SIZE*this->editor->mc->cant_col;
    int HEIGHT = SIDE_SIZE*this->editor->mc->cant_row;
    if(x < MARGIN || x > WIDTH - MARGIN){
        return false;
    }
    if(y < MARGIN || y > HEIGHT - MARGIN){
        return false;
    }
    return true;
}

static std::vector<int> get_position(std::vector<int> coordinates){
    std::vector<int> position = {};
    int x = SIDE_SIZE*(coordinates[0]-1);
    int y = SIDE_SIZE*(coordinates[1]-1);
    position.push_back(x);
    position.push_back(y);
    return position;
}

void map_actions::paint_map(int x, int y){
    if(is_inside(x,y)){
        std::vector<int> coordinates = get_coordinate(x,y);
        tile* tile = this->editor->tile_selected;
        if(this->editor->mc->paint_tile(coordinates[0]-1, coordinates[1]-1, tile)){
            std::vector<int> position = get_position(coordinates);
            QRect rect(position[0]+1, position[1]+1, SIDE_SIZE-2, SIDE_SIZE-2); //arreglar bordes segfault
            this->map->print_tile = true;
            this->map->repaint(rect);
            this->map->print_tile = false;
        }
    }
}

std::vector<int> map_actions::get_coordinate(int x, int y){

    std::vector<int> coordinates = {};

    int COL = this->editor->mc->cant_col;
    int ROW = this->editor->mc->cant_row;

    for(int i = 1; i <= COL; i++){
        float newColLine = i * SIDE_SIZE;
        if(x < newColLine + MARGIN){
            coordinates.push_back(i);
            break;
        }
    }
    for(int i = 1; i <= ROW; i++){
        float newRowLine = i * SIDE_SIZE;
        if(y < newRowLine + MARGIN){
            coordinates.push_back(i);
            break;
        }
    }
    return coordinates;
}
