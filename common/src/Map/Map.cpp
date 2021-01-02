//
// Created by joaquinfontela on 1/12/20.
//

#include "../../includes/Map/Map.h"

#include <iostream>

Map::Map(int dimx, int dimy) {
  this->dimx = dimx;
  this->dimy = dimy;
  for (int x = 1; x <= dimy; x++) {
    std::vector<Tile> tileRow;
    for (int y = 1; y <= dimx; y++) {
      Tile t(x, y);
      tileRow.push_back(t);
    }
    tileMatrix.push_back(tileRow);
  }
}

void Map::addDropWithIdAt(int id, int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  ItemDrop i(id);
  this->tileMatrix[x][y].addDrop(i);
}

std::vector<ItemDrop> Map::getItemDropsAt(int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  return this->tileMatrix[x][y].getItemDrops();
}

void Map::verifyCoordinateDoesNotSurpassMapLimits(int x, int y) {
  if ((x > this->dimx) || (y > this->dimy))
    throw std::runtime_error(
        "Error adding drop into map (map limits overpassed).");
}