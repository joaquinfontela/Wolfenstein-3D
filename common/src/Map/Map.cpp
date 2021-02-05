
//
// Created by joaquinfontela on 1/12/20.
//

#include "../../includes/Map/Map.h"

#include "../../../client/src/doortile.h"

Map::~Map() {
  free(this->matrix);
  free(this->doors);
}

float Map::getTimers(int x, int y) {
  return (this->doors + y + x * dimy)->timer;
}

int Map::get(int x, int y) { return *(this->matrix + y + x * dimy); }

bool Map::isDoor(int x, int y) { return (this->doors + y + x * dimy)->isDoor; }

void Map::switchDoorState(int x, int y) {
  (this->doors + y + x * dimy)->changeState();
}

void Map::forceDoorState(int x, int y) {
  if ((this->doors + y + x * dimy)->state == CLOSED)
    (this->doors + y + x * dimy)->state = OPEN;
  else
    (this->doors + y + x * dimy)->state = CLOSED;
}

int* Map::getMatrix() { return this->matrix; }

void Map::updateTimers(float value) {
  for (int i = 0; i < dimx; i++) {
    for (int j = 0; j < dimy; j++) {
      (this->doors + j + i * dimy)->updateTimer(value);
    }
  }
}

Map::Map(ClientMapLoader& loader) : dimx(25), dimy(25), loader(loader) {
  doors = loader.getDoorIdMatrix();
  matrix = loader.getWallIdMatrix();
}

char Map::getDoorState(int x, int y) {
  return (this->doors + y + x * dimy)->state;
}
