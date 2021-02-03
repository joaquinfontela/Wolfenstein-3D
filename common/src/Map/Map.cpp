
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

int* Map::getMatrix(){
  return this->matrix;
}

void Map::updateTimers(float value) {
  for (int i = 0; i < dimx; i++) {
    for (int j = 0; j < dimy; j++) {
      this->doors[i][j].updateTimer(value);
    }
  }
}

Map::Map(ClientMapLoader& loader) : dimx(25), dimy(25), loader(loader) {

  std::vector<Coordinate> doorCordinates = loader.getDoorCoordinates();

  for(Coordinate& c: doorCordinates){
    this->doors[c.getY() - 1][c.getX() - 1].isDoor = true;
  }

  matrix = loader.getWallIdMatrix();
}

char Map::getDoorState(int x, int y) { return this->doors[x][y].isDoor = true; }
