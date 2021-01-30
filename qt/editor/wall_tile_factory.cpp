#include "wall_tile_factory.h"

#include <string>
#include <utility>

#include "tile.h"

wall_tile_factory::wall_tile_factory() {}

tile* wall_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  QString path;
  int tipo;
  if (col == 1 && row == 4) {
    path = "./elementos_mapa/paredes/bluestone.png";
    tipo = 302;
  } else if (col == 1 && row == 3) {
    path = "./elementos_mapa/paredes/colorstone.png";
    tipo = 304;
  } else if (col == 2 && row == 5) {
    path = "./elementos_mapa/paredes/eagle.png";
    tipo = 301;
  } else if (col == 1 && row == 2) {
    path = "./elementos_mapa/paredes/greystone.png";
    tipo = 303;
  } else if (col == 1 && row == 5) {
    path = "./elementos_mapa/paredes/hitlerwall.png";
    tipo = 5;
  } else if (col == 1 && row == 1) {
    path = "./elementos_mapa/paredes/mossy.png";
    tipo = 6;
  } else if (col == 2 && row == 6) {
    path = "./elementos_mapa/paredes/propaganda.png";
    tipo = 7;
  } else if (col == 2 && row == 4) {
    path ="./elementos_mapa/paredes/purplestone.png";
    tipo = 8;
  } else if (col == 2 && row == 3) {
    path = "./elementos_mapa/paredes/redbrick.png";
    tipo = 9;
  } else if (col == 1 && row == 6) {
    path = "./elementos_mapa/paredes/skeleton.png";
    tipo = 10;
  } else if (col == 2 && row == 2) {
    path = "./elementos_mapa/paredes/greywall.png";
    tipo = 10;
  } else{
    path = "./elementos_mapa/paredes/wood.png";
    tipo = 11;
  }
  tile* tile = new class tile(path, tipo, false);
  return tile;
}
