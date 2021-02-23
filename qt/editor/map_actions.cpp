#include "map_actions.h"

#include <QMouseEvent>
#include <QPainter>
#include <QScrollEvent>
#include <iostream>
#include <vector>

#include "QCursor"
#include "QEvent"
#include "QMessageBox"
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
    if (this->editor->only_view_mode == true) {
      QMessageBox messageBox;
      messageBox.critical(0, "Error", "VIEW ONLY MODE!");
      messageBox.setFixedSize(500, 200);
      messageBox.exec();
      return true;
    }
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
    if (this->editor->mc->add_tile(coordinates, tile)) {
      Map_painter mp(this->editor->actual_tile_size(), this->map,
                     this->editor->mc);
      std::vector<tile_item*> tiles_at_coordinates =
          this->editor->mc->tiles_at_coordinates(coordinates);
      tile->add_to(this->editor->ui->graphics_map_container);
      mp.paint_map(coordinates, tiles_at_coordinates);
      tile_item* new_tile = this->editor->mc->tiles_at_coordinates(coordinates)
                                .back()
                                ->create_copy();
      this->editor->tile_item_selected = new_tile;
    }
  }
}

std::vector<int> map_actions::get_coordinate(int x, int y) {
  std::vector<int> coordinates = {};

  int COL = this->editor->mc->cant_col;
  int ROW = this->editor->mc->cant_row;
  int tile_size = this->editor->actual_tile_size();
  float shift_x =
      (this->editor->ui->graphics_map_container->width() - COL * tile_size) / 2;
  float shift_y =
      (this->editor->ui->graphics_map_container->height() - ROW * tile_size) /
      2;

  QScrollBar* vertical_bar =
      this->editor->ui->graphics_map_container->verticalScrollBar();
  QScrollBar* horizontal_bar =
      this->editor->ui->graphics_map_container->horizontalScrollBar();

  for (int i = 1; i <= COL; i++) {
    float newColLine = i * tile_size - horizontal_bar->value();
    if (shift_x > 0) {
      newColLine += shift_x;
    }
    if (x < newColLine) {
      coordinates.push_back(i);
      break;
    }
  }
  for (int i = 1; i <= ROW; i++) {
    float newRowLine = i * tile_size - vertical_bar->value();
    if (shift_y > 0) {
      newRowLine += shift_y;
    }
    if (y < newRowLine) {
      coordinates.push_back(i);
      break;
    }
  }

  if (coordinates.size() != 2 || x < shift_x || y < shift_y) {
    return {-1, -1};
  }

  return coordinates;
}
