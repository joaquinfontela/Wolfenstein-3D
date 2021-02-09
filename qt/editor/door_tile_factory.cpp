#include "door_tile_factory.h"

#include "tile_item.h"

door_tile_factory::door_tile_factory() {}

tile_item* door_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  bool comulative = false;
  int tipo;
  if (col == 1 && row == 1) {
    tipo = 201;
  } else if (col == 1 && row == 2) {
    tipo = 202;
  } else if (col == 2 && row == 1) {
    tipo = 203;
  } else {
    tipo = 108;
    comulative = true;
  }
  std::string path(PathFactory().getTilePath(tipo).c_str());
  tile_item* tile = new class tile_item(path, tipo, comulative);
  return tile;
}
