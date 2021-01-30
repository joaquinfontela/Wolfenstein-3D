#include "decoration_tile_factory.h"

#include "tile.h"

decoration_tile_factory::decoration_tile_factory() {}

tile* decoration_tile_factory::get_tile(std::vector<int>& coordinates) {
  int col = coordinates[0];
  int row = coordinates[1];
  QString path;
  int tipo;
  if (col == 1 && row == 2) {
    path = "./elementos_mapa/decoraciones/barrel.png";
    tipo = 1;
  } else if (col == 2 && row == 4) {
    path = "./elementos_mapa/decoraciones/cageskeleton.png";
    tipo = 2;
  } else if (col == 2 && row == 6) {
    path = "./elementos_mapa/decoraciones/flag.png";
    tipo = 3;
  } else if (col == 1 && row == 6) {
    path = "./elementos_mapa/decoraciones/floorlamp.png";
    tipo = 4;
  } else if (col == 1 && row == 7) {
    path = "./elementos_mapa/decoraciones/greenbarrel.png";
    tipo = 5;
  } else if (col == 2 && row == 2) {
    path = "./elementos_mapa/decoraciones/greenlight.png";
    tipo = 6;
  } else if (col == 1 && row == 7) {
    path = "./elementos_mapa/decoraciones/groundskeleton.png";
    tipo = 7;
  } else if (col == 2 && row == 5) {
    path ="./elementos_mapa/decoraciones/heapofbones.png";
    tipo = 8;
  } else if (col == 1 && row == 3) {
    path = "./elementos_mapa/decoraciones/hungskeleton.png";
    tipo = 9;
  } else if (col == 2 && row == 1) {
    path = "./elementos_mapa/decoraciones/pillar.png";
    tipo = 10;
  } else if (col == 1 && row == 4) {
    path = "./elementos_mapa/decoraciones/plant.png";
    tipo = 11;
  } else if (col == 1 && row == 5) {
    path = "./elementos_mapa/decoraciones/spikes.png";
    tipo = 12;
  } else if (col == 2 && row == 3) {
    path = "./elementos_mapa/decoraciones/table.png";
    tipo = 13;
  } else{
    path = "./elementos_mapa/decoraciones/water.png";
    tipo = 14;
  }
  tile* tile = new class tile(path, tipo, true);
  return tile;
}
