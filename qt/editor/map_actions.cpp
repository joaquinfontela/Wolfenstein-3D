#include "map_actions.h"

#include <QMouseEvent>
#include <QPainter>
#include <QScrollEvent>
#include <iostream>
#include <vector>

#include "QCursor"
#include "QEvent"
#include "QScrollBar"
#include "map_painter.h"
#include "map_scene.h"
#include "ui_editor.h"

map_actions::map_actions(Editor* editor, map_scene* map_to_paint) {
  this->editor = editor;
  this->map = map_to_paint;
}

bool map_actions::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent* me = (QMouseEvent*)event;
    int x = me->pos().x();
    int y = me->pos().y();
    if (this->editor->eraser_on == false) {
      add_to_map(x, y);
    } else {
      editor->mc->erase_tiles_at(this->get_coordinate(x, y));
    }
    return true;
  } else {
    return QObject::eventFilter(obj, event);
  }
}

void map_actions::add_to_map(int x, int y) {
  if (editor->tile_item_selected != NULL) {
    std::vector<int> coordinates = get_coordinate(x, y);
    tile_item* tile = this->editor->tile_item_selected;
    if (this->editor->mc->paint_tile(coordinates, tile)) {
      Map_painter* mp = new Map_painter(this->editor->actual_tile_size(),
                                        this->map, this->editor->mc);
      std::vector<tile_item*> tiles_at_coordinates =
          this->editor->mc->tiles_at_coordinates(coordinates);
      tile->add_to(this->editor->ui->graphics_map_container);
      mp->paint_map(coordinates, tiles_at_coordinates);
      this->editor->tile_item_selected =
          this->editor->tile_item_selected->create_copy();
    }
  }
}

std::vector<int> map_actions::get_coordinate(int x, int y) {
  std::vector<int> coordinates = {};

  int COL = this->editor->mc->cant_col;
  int ROW = this->editor->mc->cant_row;
  int tile_size = this->editor->actual_tile_size();
  QScrollBar* vertical_bar =
      this->editor->ui->graphics_map_container->verticalScrollBar();
  QScrollBar* horizontal_bar =
      this->editor->ui->graphics_map_container->horizontalScrollBar();

  for (int i = 1; i <= COL; i++) {
    float newColLine = i * tile_size - horizontal_bar->value();
    if (x < newColLine) {
      coordinates.push_back(i);
      break;
    }
  }
  for (int i = 1; i <= ROW; i++) {
    float newRowLine = i * tile_size - vertical_bar->value();
    if (y < newRowLine) {
      coordinates.push_back(i);
      break;
    }
  }
  return coordinates;
}
