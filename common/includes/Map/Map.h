#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <string>
#include "../../../client/src/clientprotocol.h"
#include "../../../client/src/ClientMapLoader.h"
#include <cstring>

class Map {
 public:
  // ¡CAMBIAR POR DEFINES EN EL PROTOCOLO!
  float doors[24][24];
  int* matrix;
  int dimx;
  int dimy;
  ClientMapLoader& loader;

  Map(ClientMapLoader& loader);
  ~Map();
  int get(int x, int y);
  float getDoor(int x, int y);
  void openDoor(int x, int y);
  void switchDoorState(int x, int y);
};

#endif  // TP_FINAL_MAP_H
