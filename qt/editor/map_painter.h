#ifndef MAP_PAINTER_H
#define MAP_PAINTER_H

#include <vector>

#include "map_canvas.h"
#include "map_scene.h"
#include "tile_item.h"

class Map_painter {
 private:
  int tile_size;
  map_scene* scene;
  map_canvas* mc;
  /**
   * @return a size two vector representing a position in the window that
   * matches with the coordinate of the map specified by coordinates.
   *
   * @param coordinates a size two vector representing a map coordinate.
   */
  std::vector<int> get_position(std::vector<int> coordinates);
  /**
   * @brief Paints an object that covers the whole tile in the specified by
   * position.
   *
   * @param position a two-sized vector that represents a coordinate where the
   * object wil be painted.
   * @param tile the object that identifies the tile item to be painted.
   */
  void paint_big_tile(std::vector<int> position, tile_item* tile);
  /**
   * @brief Paints two to four objects (depending on tiles size) in the tile
   * specified by position.
   *
   * @param position a two-sized vector that represents a coordinate where the
   * object wil be painted.
   * @param tiles a vector of pointers to tile items, each of them identifying
   * an item to be painted.
   */
  void paint_multiple_tile(std::vector<int> position,
                           std::vector<tile_item*> tiles);

  void erase_panting(std::vector<int> coordinates);

 public:
  Map_painter(int tile_size, map_scene* map_to_paint, map_canvas* map_canvas);
  /**
   * @brief Renders the tiles recieved in the coordinate especified.
   *
   * @param coordinates a two-sized vector that represents a coordinate.
   * @param tiles a vector of pointers to tile_items.
   */
  void paint_map(std::vector<int> coordinates, std::vector<tile_item*> tiles);
  /**
   * @brief Paints all the tiles of the map canvas.
   */
  void paint_all_tiles();
};

#endif  // MAP_PAINTER_H
