#include "item_tile_factory.h"

#include "tile_item.h"

item_tile_factory::item_tile_factory() {}

tile_item* item_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  int tipo;
  if (col == 2 && row == 3) {
    tipo = 124;
  } else if (col == 1 && row == 4) {
    tipo = 101;
  } else if (col == 1 && row == 3) {
    tipo = 102;
  } else if (col == 2 && row == 2) {
    tipo = 4;
  } else if (col == 1 && row == 2) {
    tipo = 103;
  } else if (col == 2 && row == 5) {
    tipo = 107;
  } else if (col == 2 && row == 6) {
    tipo = 104;
  } else if (col == 1 && row == 5) {
    tipo = 105;
  } else if (col == 2 && row == 4) {
    tipo = 106;
  } else if (col == 1 && row == 6) {
    tipo = 109;
  } else if (col == 2 && row == 1) {
    tipo = 3;
  } else {
    tipo = 5;
  }
  std::string path(PathFactory().getTilePath(tipo).c_str());
  tile_item* tile = new class tile_item(path, tipo, true);
  return tile;
}
