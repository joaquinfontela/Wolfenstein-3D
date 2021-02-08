#include "map_canvas.h"

#include <QMessageBox>
#include <iostream>
#include <vector>

#include "tile_item.h"

map_canvas::map_canvas(int col, int row) {
  this->grilla = {};
  for (int i = 0; i < row; i++) {
    std::vector<std::vector<tile_item*>> new_row;
    for (int x = 0; x < col; x++) {
      std::vector<tile_item*> col_vector;
      new_row.push_back(col_vector);
    }
    grilla.push_back(new_row);
  }
  this->cant_col = col;
  this->cant_row = row;
}
map_canvas::map_canvas(TileMatrix* tile_matrix) {
  this->cant_col = tile_matrix->at(0).size();
  this->cant_row = tile_matrix->size();
  for (int i = 0; i < cant_row; i++) {
      std::vector<std::vector<tile_item*>> new_row;
      for (int x = 0; x < cant_col; x++) {
          std::vector<tile_item*> col_vector;
          std::vector<tile_item*> vector_tile_matrix = tile_matrix->at(i).at(x);
          for(size_t y = 0; y < vector_tile_matrix.size(); y++){
                col_vector.push_back(vector_tile_matrix.at(y)->create_copy());
          }
        new_row.push_back(col_vector);
      }
      grilla.push_back(new_row);
    }
}

bool map_canvas::add_tile(std::vector<int> coordinates, tile_item* new_tile) {
  int col = coordinates[0] - 1;
  int row = coordinates[1] - 1;
  std::vector<tile_item*> vector_selected = this->grilla.at(row).at(col);

  if (vector_selected.empty() || (this->grilla.at(row).at(col).at(0)->accept_tile(new_tile) &&
                                  vector_selected.size() < 4)) {
    this->grilla.at(row).at(col).push_back(new_tile);
    return true;
  }
  return false;
}

std::vector<tile_item*> map_canvas::tiles_at_coordinates(std::vector<int> coordinates) {
  return this->grilla.at(coordinates[1] - 1).at(coordinates[0] - 1);
}

void map_canvas::erase_tiles_at(std::vector<int> coordinates) {
  int col = coordinates[0] - 1;
  int row = coordinates[1] - 1;
  size_t vector_size = this->grilla.at(row).at(col).size();
  for (size_t i = 0; i < vector_size; i++) {
      tile_item* tile = this->grilla.at(row).at(col).back();
      delete tile;
      this->grilla.at(row).at(col).pop_back();
  }
}

map_canvas::~map_canvas(){

}
