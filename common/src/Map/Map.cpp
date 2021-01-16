
//
// Created by joaquinfontela on 1/12/20.
//

#include "../../includes/Map/Map.h"
#include "../../../client/src/doortile.h"

Map::~Map() {
  // No se puede dejar este free acá. Debería estar en el
  // destructor del loader. Si el lo crea el lo destruye.
  free(this->matrix);
}

int Map::get(int x, int y) { return *(this->matrix + y + x*dimy); }

bool Map::isDoor(int x, int y) { return this->doors[x][y].isDoor; }

void Map::switchDoorState(int x, int y) {
  doors[x][y].changeState();
}

void Map::forceDoorState(int x, int y) {
  if (doors[x][y].state == CLOSED)
    doors[x][y].state = OPEN;
  else
    doors[x][y].state = CLOSED;
}

Map::Map(ClientMapLoader& loader) : dimx(25), dimy(25), loader(loader) {
  this->doors[11][2].setDoor(true);
  this->doors[9][5].setDoor(true);
  this->doors[11][6].setDoor(true);
  this->doors[7][9].setDoor(true);
  this->doors[3][12].setDoor(true);
  this->doors[11][13].setDoor(true);
  this->doors[22][18].setDoor(true);
  this->doors[6][19].setDoor(true);
  this->doors[22][19].setDoor(true);
  matrix = loader.getWallIdMatrix();
}

char Map::getDoorState(int x, int y) { return this->doors[x][y].state; }
