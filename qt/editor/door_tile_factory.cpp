#include "door_tile_factory.h"

#include "tile.h"

door_tile_factory::door_tile_factory() {}

tile* door_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  bool comulative = false;
  QString path;
  int tipo;
  if (col == 1 && row == 1) {
    path = "./elementos_mapa/puertas/dark_door.png";
    tipo = 1;
  } else if (col == 1 && row == 2) {
    path = "./elementos_mapa/puertas/iron_door.png";
    tipo = 2;
  } else if (col == 2 && row == 1) {
    path = "./elementos_mapa/puertas/blue_door.png";
    tipo = 3;
  } else {
    path = "./elementos_mapa/puertas/goldenkey.png";
    tipo = 4;
    comulative = true;
  }
  tile* tile = new class tile(path, tipo, comulative);
  return tile;
}
