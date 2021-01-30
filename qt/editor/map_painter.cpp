#include "map_painter.h"
#include "my_map.h"
#include "map_canvas.h"

#define WHITE_BOX_PATH "./fondo_blanco.png"
#define MARGIN 7

Map_painter::Map_painter(int tile_size, my_map& map_to_paint) : map(map_to_paint){
    this->tile_size = tile_size;
}

std::vector<int> Map_painter:: get_position(std::vector<int> coordinates) {
  std::vector<int> position = {};
  int x = tile_size * (coordinates[0] - 1) + 1;
  int y = tile_size * (coordinates[1] - 1) + 1;
  position.push_back(x);
  position.push_back(y);
  return position;
}

void Map_painter::erase_panting(std::vector<int> position) {
  QRect rect_0(position[0], position[1], tile_size - 2, tile_size - 2);
  this->map.tile_to_paint = new tile(WHITE_BOX_PATH, 0, false);
  this->map.repaint(rect_0);
}

void Map_painter::paint_big_tile(std::vector<int> position, tile* tile) {
  int tile_size = this->tile_size - 2;
  QRect rect(position[0], position[1], tile_size, tile_size);
  this->map.tile_to_paint = tile;
  this->map.repaint(rect);
}

void Map_painter::paint_multiple_tile(std::vector<int> position,
                                      std::vector<tile*> tiles) {
  int tile_size = this->tile_size / 2 - 2;

  QRect rect_5(position[0], position[1], tile_size, tile_size);
  this->map.tile_to_paint = tiles.at(0);
  this->map.repaint(rect_5);

  QRect rect_2(position[0] + tile_size, position[1] + tile_size, tile_size,
               tile_size);
  this->map.tile_to_paint = tiles.at(1);
  this->map.repaint(rect_2);

  if (this->map.tiles_to_paint > 2) {
    QRect rect_3(position[0] + tile_size, position[1], tile_size, tile_size);
    this->map.tile_to_paint = tiles.at(2);
    this->map.repaint(rect_3);
  }
  if (this->map.tiles_to_paint > 3) {
    QRect rect_4(position[0], position[1] + tile_size, tile_size, tile_size);
    this->map.tile_to_paint = tiles.at(3);
    this->map.repaint(rect_4);
  }
}

void Map_painter::paint_map(std::vector<int> coordinates, std::vector<tile*> tiles) {
  std::vector<int> position = get_position(coordinates);
  this->map.tiles_to_paint = tiles.size();
  this->erase_panting(position);
  if (this->map.tiles_to_paint == 1) {
    this->paint_big_tile(position, tiles[0]);
  } else {
    this->paint_multiple_tile(position, tiles);
  }
  this->map.tiles_to_paint = 0;
}

void Map_painter::paint_all_tiles(map_canvas* mc){
    for(int i = 1; i < mc->cant_row; i++){
        for(int x = 1; x < mc->cant_row; x++){
            std::vector<tile*> tiles = mc->tiles_at_coordinates({i,x});
            if(!tiles.empty() && tiles.at(0) != 0){
                this->paint_map({i,x}, mc->tiles_at_coordinates({i,x}));
            }
        }
    }
}
