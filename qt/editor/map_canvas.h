#ifndef MAP_CANVAS_H
#define MAP_CANVAS_H

#include <QFrame>
#include <vector>

#include "tile_item.h"

typedef std::vector<std::vector<std::vector<tile_item*>>> TileMatrix;

class map_canvas : public QFrame {
 public:
  map_canvas(int col, int row);
  map_canvas(TileMatrix* tile_matrix);
  ~map_canvas();

  /**
   * @brief Adds the tile to the coordinates recieved.
   *
   * @param coordinates a two-sized vector that represents a coordinate.
   * @param tile a pointer to the tile item that will be added.
   * @return true if the tile was added correctly, or false otherwise.
   */
  bool add_tile(std::vector<int> coordinates, tile_item* tile);
  /**
   * @brief get the tile items that are in the position of coordinates.
   * @param coordinates a two-sized vector that represents a coordinate .
   * @return a vector of pointers to tile items that are in coordinates.
   */
  std::vector<tile_item*> tiles_at_coordinates(std::vector<int> coordinates);
  /**
   * @brief Erases and deletes the dynamic pointers of all the tiles present at
   * coordinates.
   *
   * @param coordinates a two-sized vector that represents a coordinate.
   */
  void erase_tiles_at(std::vector<int> coordinates);

  bool is_empty();

  TileMatrix grilla;
  int cant_col;
  int cant_row;
};

#endif  // MAP_CANVAS_H
