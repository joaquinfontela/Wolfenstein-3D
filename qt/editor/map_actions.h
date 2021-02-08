#ifndef MAP_ACTIONS_H
#define MAP_ACTIONS_H

#include <QObject>
#include <vector>

#include "editor.h"
#include "map_scene.h"
#include "ui_editor.h"

class map_actions : public QObject {
  Editor* editor;
  map_scene* map;

 public:
  map_actions(Editor* editor, map_scene* map_to_paint);
  bool eventFilter(QObject* obj, QEvent* event);
  /**
   * @brief Renders the selected tile in the map and adds it into the matrix.
   *
   * @param x the x component of the mouse click event in the map.
   * @param y the y component of the mouse click event in the map.
   */
  void add_to_map(int x, int y);
  /**
   * @brief Returns the coordinate of the map that matches the coordinate of the
   * mouse click event.
   *
   * @param x the x component of the mouse click event in the map.
   * @param y the y component of the mouse click event in the map.
   * @return a vector of size two representing a coordinate of the map.
   */
  std::vector<int> get_coordinate(int x, int y);
};

#endif  // MAP_ACTIONS_H
