#include "item_tile_factory.h"

#include "tile.h"

item_tile_factory::item_tile_factory() {}

tile* item_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  QString path;
  int tipo;
  if (col == 2 && row == 3) {
    path = "./elementos_mapa/items/1up.png";
    tipo = 1;
  } else if (col == 1 && row == 4) {
    path = "./elementos_mapa/items/ammo.png";
    tipo = 2;
  } else if (col == 1 && row == 3) {
    path = "./elementos_mapa/items/blood.png";
    tipo = 3;
  } else if (col == 2 && row == 2) {
    path = "./elementos_mapa/items/chaingunitem.png";
    tipo = 4;
  } else if (col == 1 && row == 2) {
    path = "./elementos_mapa/items/chest.png";
    tipo = 5;
  } else if (col == 2 && row == 5) {
    path = "./elementos_mapa/items/food.png";
    tipo = 6;
  } else if (col == 1 && row == 6) {
    path = "./elementos_mapa/items/goldencross.png";
    tipo = 7;
  } else if (col == 1 && row == 5) {
    path = "./elementos_mapa/items/goldencrown.png";
    tipo = 8;
  } else if (col == 2 && row == 4) {
    path = "./elementos_mapa/items/goldencup.png";
    tipo = 9;
  } else if (col == 1 && row == 6) {
    path = "./elementos_mapa/items/medkit.png";
    tipo = 10;
  } else if (col == 2 && row == 1) {
    path = "./elementos_mapa/items/machinegunitem.png";
    tipo = 11;
  } else{
    path = "./elementos_mapa/items/rocketlauncheritem.png";
    tipo = 12;
  }
  tile* tile = new class tile(path, tipo, true);
  return tile;
}
