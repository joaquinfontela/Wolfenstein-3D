
//
// Created by joaquinfontela on 1/12/20.
//

#include "../../includes/Map/Map.h"

Map::~Map() {
  // No se puede dejar este free acá. Debería estar en el
  // destructor del loader. Si el lo crea el lo destruye.
  free(this->matrix);
}

Map::Map(ClientMapLoader& loader) : dimx(25), dimy(25), loader(loader) {
  memset(this->doors, 0, sizeof(this->doors));
  this->doors[11][2] = DOOR_CLOSED;
  this->doors[9][5] = DOOR_CLOSED;
  this->doors[11][6] = DOOR_CLOSED;
  this->doors[7][9] = DOOR_CLOSED;
  this->doors[3][12] = DOOR_CLOSED;
  this->doors[11][13] = DOOR_CLOSED;
  this->doors[22][18] = DOOR_CLOSED;
  this->doors[6][19] = DOOR_CLOSED;
  this->doors[22][19] = DOOR_CLOSED;

  matrix = loader.getWallIdMatrix();
}

int Map::get(int x, int y) { return *(this->matrix + y + x*25); }

float Map::getDoor(int x, int y) { return doors[x][y]; }

void Map::openDoor(int x, int y) { doors[x][y] = DOOR_OPEN; }

void Map::switchDoorState(int x, int y) {
  if (doors[x][y] == DOOR_OPEN)
    doors[x][y] = DOOR_CLOSED;
  else
    doors[x][y] = DOOR_OPEN;
}
