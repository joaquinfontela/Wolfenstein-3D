#include "door_tile_factory.h"

#include "tile.h"

door_tile_factory::door_tile_factory() {}

tile* door_tile_factory::get_tile(std::vector<int>& coordinates) {
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
  QString path(PathFactory().getTilePath(tipo).c_str());
  tile* tile = new class tile(path, tipo, false);
  return tile;
}
