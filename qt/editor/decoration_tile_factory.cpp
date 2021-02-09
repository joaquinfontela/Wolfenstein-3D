#include "decoration_tile_factory.h"

#include "tile_item.h"

decoration_tile_factory::decoration_tile_factory() {}

tile_item* decoration_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  int tipo;
  if (col == 1 && row == 2) {
    tipo = 110;
  } else if (col == 2 && row == 4) {
    tipo = 111;
  } else if (col == 2 && row == 6) {
    tipo = 112;
  } else if (col == 1 && row == 6) {
    tipo = 113;
  } else if (col == 1 && row == 7) {
    tipo = 114;
  } else if (col == 2 && row == 2) {
    tipo = 115;
  } else if (col == 2 && row == 7) {
    tipo = 116;
  } else if (col == 2 && row == 5) {
    tipo = 117;
  } else if (col == 1 && row == 3) {
    tipo = 118;
  } else if (col == 2 && row == 1) {
    tipo = 119;
  } else if (col == 1 && row == 4) {
    tipo = 120;
  } else if (col == 1 && row == 5) {
    tipo = 121;
  } else if (col == 2 && row == 3) {
    tipo = 122;
  } else {
    tipo = 123;
  }
  std::string path(PathFactory().getTilePath(tipo).c_str());
  tile_item* tile = new class tile_item(path, tipo, true);
  return tile;
}
