#include "map_actions.h"

#include <QMouseEvent>
#include <QPainter>
#include <iostream>

#include "QCursor"
#include "QEvent"
#include "my_map.h"
#include "tile.h"

#define MARGIN 7
#define SIDE_SIZE 40

map_actions::map_actions(Editor* editor, my_map* map) {
  this->editor = editor;
  this->map = map;
}

bool map_actions::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent* me = (QMouseEvent*)event;
    int x = me->localPos().x();
    int y = me->localPos().y();
    add_to_map(x, y);
    return true;
  } else {
    return QObject::eventFilter(obj, event);
  }
}

bool map_actions::is_inside(int x, int y) {
  int WIDTH = SIDE_SIZE * this->editor->mc->cant_col;
  int HEIGHT = SIDE_SIZE * this->editor->mc->cant_row;
  if (x < MARGIN || x > WIDTH - MARGIN) {
    return false;
  }
  if (y < MARGIN || y > HEIGHT - MARGIN) {
    return false;
  }
  return true;
}

static std::vector<int> get_position(std::vector<int> coordinates) {
  std::vector<int> position = {};
  int x = SIDE_SIZE * (coordinates[0] - 1);
  int y = SIDE_SIZE * (coordinates[1] - 1);
  position.push_back(x);
  position.push_back(y);
  return position;
}

void map_actions::erase_panting(std::vector<int> position) {
  QRect rect_0(position[0] + 1, position[1] + 1, SIDE_SIZE - 1, SIDE_SIZE - 1);
  this->map->tile_to_paint = new tile("./fondo_blanco.png", 0, false);
  this->map->repaint(rect_0);
}

void map_actions::paint_big_tile(std::vector<int> position, tile* tile) {
  int tile_size = SIDE_SIZE - 1;
  QRect rect(position[0], position[1], tile_size, tile_size);
  this->map->tile_to_paint = tile;
  this->map->repaint(rect);
}

void map_actions::paint_multiple_tile(std::vector<int> position,
                                      std::vector<tile*> tiles) {
  int tile_size = SIDE_SIZE / 2 - 1;

  QRect rect_5(position[0], position[1], tile_size, tile_size);
  this->map->tile_to_paint = tiles.at(0);
  this->map->repaint(rect_5);

  QRect rect_2(position[0] + tile_size, position[1] + tile_size, tile_size,
               tile_size);
  this->map->tile_to_paint = tiles.at(1);
  this->map->repaint(rect_2);

  if (this->map->tiles_to_paint > 2) {
    QRect rect_3(position[0] + tile_size, position[1], tile_size, tile_size);
    this->map->tile_to_paint = tiles.at(2);
    this->map->repaint(rect_3);
  }
  if (this->map->tiles_to_paint > 3) {
    QRect rect_4(position[0], position[1] + tile_size, tile_size, tile_size);
    this->map->tile_to_paint = tiles.at(3);
    this->map->repaint(rect_4);
  }
}

void map_actions::paint_map(std::vector<int> coordinates) {
  std::vector<int> position = get_position(coordinates);
  std::vector<tile*> tiles =
      this->editor->mc->tiles_at_coordinates(coordinates);
  this->map->tiles_to_paint = tiles.size();
  this->erase_panting(position);
  if (this->map->tiles_to_paint == 1) {
    this->paint_big_tile(position, tiles[0]);
  } else {
    this->paint_multiple_tile(position, tiles);
  }
  this->map->tiles_to_paint = 0;
}

void map_actions::add_to_map(int x, int y) {
  if (is_inside(x, y) && editor->tile_selected != NULL) {
    std::vector<int> coordinates = get_coordinate(x, y);
    tile* tile = this->editor->tile_selected;
    if (this->editor->mc->paint_tile(coordinates, tile)) {
      this->paint_map(coordinates);
    }
  }
}

std::vector<int> map_actions::get_coordinate(int x, int y) {
  std::vector<int> coordinates = {};

  int COL = this->editor->mc->cant_col;
  int ROW = this->editor->mc->cant_row;

  for (int i = 1; i <= COL; i++) {
    float newColLine = i * SIDE_SIZE;
    if (x < newColLine + MARGIN) {
      coordinates.push_back(i);
      break;
    }
  }
  for (int i = 1; i <= ROW; i++) {
    float newRowLine = i * SIDE_SIZE;
    if (y < newRowLine + MARGIN) {
      coordinates.push_back(i);
      break;
    }
  }
  return coordinates;
}
