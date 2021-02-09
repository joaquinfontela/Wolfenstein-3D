#include "map_painter.h"

#include "iostream"
#include "map_canvas.h"
#include "map_scene.h"
#include "tile_item.h"

#define WHITE_BOX_PATH "./fondo_blanco.png"
#define MARGIN 7

Map_painter::Map_painter(int tile_size, map_scene* map_to_paint,
                         map_canvas* map_canvas) {
  this->tile_size = tile_size;
  this->scene = map_to_paint;
  this->mc = map_canvas;
}

std::vector<int> Map_painter::get_position(std::vector<int> coordinates) {
  std::vector<int> position = {};
  int x = tile_size * (coordinates[0] - 1) - 2;
  int y = tile_size * (coordinates[1] - 1) - 2;
  position.push_back(x);
  position.push_back(y);
  return position;
}

void Map_painter::paint_big_tile(std::vector<int> position, tile_item* tile) {
  tile->configure_rect(tile_size, position[0], position[1]);
  this->scene->addItem(tile);
  tile->update();
}

void Map_painter::paint_multiple_tile(std::vector<int> position,
                                      std::vector<tile_item*> tiles) {
  int tile_mini_size = this->tile_size / 2;

  tiles.at(0)->configure_rect(tile_mini_size, position[0], position[1]);
  this->scene->addItem(tiles.at(0));
  tiles.at(0)->update();

  tiles.at(1)->configure_rect(tile_mini_size, position[0] + tile_mini_size,
                              position[1] + tile_mini_size);
  this->scene->addItem(tiles.at(1));
  tiles.at(1)->update();

  size_t tiles_to_paint = tiles.size();
  if(tiles_to_paint > 2){
      tiles.at(2)->configure_rect(tile_mini_size, position[0],
                                  position[1] + tile_mini_size);
      this->scene->addItem(tiles.at(2));
      tiles.at(2)->update();
  }
  if(tiles_to_paint > 3){
      tiles.at(3)->configure_rect(tile_mini_size, position[0] + tile_mini_size,
                                  position[1]);
      this->scene->addItem(tiles.at(3));
      tiles.at(3)->update();
  }
}

void Map_painter::paint_map(std::vector<int> coordinates,
                            std::vector<tile_item*> tiles) {
  std::vector<int> position = get_position(coordinates);
  if (tiles.size() > 1) {
    std::vector<tile_item*> tile_backup;

    for (size_t i = 0; i < tiles.size(); i++) {
      tile_backup.push_back(tiles.at(i)->create_copy());
    }
    this->mc->erase_tiles_at(coordinates);
    this->paint_multiple_tile(position, tile_backup);
    for (size_t x = 0; x < tile_backup.size(); x++) {
      this->mc->add_tile(coordinates, tile_backup.at(x));
    }
  } else {
    this->paint_big_tile(position, tiles.at(0));
  }
}

void Map_painter::paint_all_tiles() {
  for (int i = 0; i < mc->cant_row; i++) {
    for (int x = 0; x < mc->cant_row; x++) {
      std::vector<tile_item*> tiles = mc->tiles_at_coordinates({i+1, x+1});
      if (!tiles.empty()) {
        this->paint_map({i+1, x+1}, tiles);
      }
    }
  }
}
