
//
// Created by joaquinfontela on 1/12/20.
//

#include "../../includes/Map/Map.h"

Map::~Map() {
  // No se puede dejar este free acá. Debería estar en el
  // destructor del loader. Si el lo crea el lo destruye.
  free(this->matrix);
}

Map::Map(ClientMapLoader& loader) : dimx(24), dimy(24), loader(loader) {
  memset(this->doors, 0, sizeof(this->doors));
  this->doors[3][12] = DOOR_CLOSED;
  this->doors[6][10] = DOOR_CLOSED;
  this->doors[7][12] = DOOR_CLOSED;
  this->doors[12][3] = DOOR_CLOSED;
  this->doors[13][11] = DOOR_CLOSED;
  this->doors[18][22] = DOOR_CLOSED;
  this->doors[19][6] = DOOR_CLOSED;
  this->doors[19][22] = DOOR_CLOSED;
  matrix = loader.getWallIdMatrix();
}

int Map::get(int x, int y) { return *(this->matrix + y + x*24); }

float Map::getDoor(int x, int y) { return doors[x][y]; }

void Map::openDoor(int x, int y) { doors[x][y] = DOOR_OPEN; }

void Map::switchDoorState(int x, int y) {
  if (doors[x][y] == DOOR_OPEN)
    doors[x][y] = DOOR_CLOSED;
  else
    doors[x][y] = DOOR_OPEN;
}
