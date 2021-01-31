#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <string>
#include "../../../client/src/doortile.h"
#include "../../../client/src/clientprotocol.h"
#include "../../../client/src/ClientMapLoader.h"
#include <cstring>

class Map {
 public:
  // ¡CAMBIAR POR DEFINES EN EL PROTOCOLO!
  DoorTile doors[25][25];
  int* matrix;
  int dimx;
  int dimy;
  ClientMapLoader& loader;

  Map(ClientMapLoader& loader);
  ~Map();
  void updateTimers(float value);
  int get(int x, int y);
  bool isDoor(int x, int y);
  char getDoorState(int x, int y);
  void switchDoorState(int x, int y);
  void forceDoorState(int x, int y);
  int* getMatrix();
};

#endif  // TP_FINAL_MAP_H
