#include "map_actions.h"
#include <vector>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include <QScrollEvent>
#include "QCursor"
#include "QEvent"
#include "my_map.h"
#include "tile.h"
#include "map_painter.h"
#include "ui_editor.h"

#define MARGIN 7

map_actions::map_actions(Editor* editor, my_map& map_to_paint) : map(map_to_paint){
  this->editor = editor;
}

bool map_actions::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent* me = (QMouseEvent*)event;
    int x = me->localPos().x();
    int y = me->localPos().y();
    add_to_map(x, y);
    return true;
  }  else {
    return QObject::eventFilter(obj, event);
  }
}

void map_actions::add_to_map(int x, int y) {
  if (is_inside(x, y) && editor->tile_selected != NULL) {
    std::vector<int> coordinates = get_coordinate(x, y);
    tile* tile = this->editor->tile_selected;
    if (this->editor->mc->paint_tile(coordinates, tile)) {
      Map_painter* mp = new Map_painter(this->editor->actual_tile_size(), this->map);
      mp->paint_map(coordinates, this->editor->mc->tiles_at_coordinates(coordinates));
      //editor->update_map_container(this->map);
    }
  }
}

std::vector<int> map_actions::get_coordinate(int x, int y) {
  std::vector<int> coordinates = {};

  int COL = this->editor->mc->cant_col;
  int ROW = this->editor->mc->cant_row;
  int tile_size = this->editor->actual_tile_size();

  for (int i = 1; i <= COL; i++) {
    float newColLine = i * tile_size;
    if (x < newColLine + MARGIN) {
      coordinates.push_back(i);
      break;
    }
  }
  for (int i = 1; i <= ROW; i++) {
    float newRowLine = i * tile_size;
    if (y < newRowLine + MARGIN) {
      coordinates.push_back(i);
      break;
    }
  }
  return coordinates;
}

bool map_actions::is_inside(int x, int y) {
  int tile_size = this->editor->actual_tile_size();
  int WIDTH = tile_size * this->editor->mc->cant_col;
  int HEIGHT = tile_size * this->editor->mc->cant_row;
  if (x < MARGIN || x > WIDTH - MARGIN) {
    return false;
  }
  if (y < MARGIN || y > HEIGHT - MARGIN) {
    return false;
  }
  return true;
}
