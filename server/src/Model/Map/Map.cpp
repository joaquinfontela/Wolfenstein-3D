//
// Created by joaquinfontela on 1/12/20.
//

#include "../../../includes/Model/Map/Map.h"

#include <iostream>
#include <tuple>

unsigned int Map::nextId = 1;

Map::Map(int dimx, int dimy) {
  this->dimx = dimx;
  this->dimy = dimy;
  for (int x = 0; x < dimy; x++) {
    std::vector<Tile> tileRow;
    for (int y = 0; y < dimx; y++) {
      Tile t;
      tileRow.push_back(t);
    }
    tileMatrix.push_back(tileRow);
  }
}

void Map::addItemDropAt(Item* item, int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addItemDrop(item);
}

void Map::addWeaponDropAt(Weapon* weapon, int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addWeaponDrop(weapon);
}

void Map::addDoorAt(Door* door, int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addDoor(door);
}

void Map::addWallAt(Wall* wall, int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addWall(wall);
}

void Map::verifyCoordinateDoesNotSurpassMapLimits(int x, int y) {
  if ((x > this->dimx) || (x < 1) || (y > this->dimy) || (y < 1))
    throw std::runtime_error(
        "Error adding item into map (map limits overpassed).");
}

Player* Map::traceAttackFrom(Player* attacker) {
  double initialX = attacker->getX();
  double initialY = attacker->getY();

  double dirX = attacker->getDirX() / 3.0;
  double dirY = attacker->getDirY() / 3.0;

  int i = 1;

  Player* p = nullptr;

  while (true) {
    double rayPosX = (initialX + i * dirX);
    double rayPosY = (initialY + i * dirY);

    int mapX = (int)rayPosX;
    int mapY = (int)rayPosY;

    if (this->tileMatrix.at(mapX).at(mapY).checkWall())
      return nullptr;

    else if ((p = this->tileMatrix.at(mapX).at(mapY).playerCollision(
                  rayPosX, rayPosY, attacker)) != nullptr)
      return p;

    i++;
  }
}

std::tuple<double, double> Map::handleRespawn() {
  return std::make_tuple(6, 4);
}
bool Map::moveTo(double fromX, double fromY, double toX, double toY,
                 Player* p) {
  int x = (int)toX;
  int y = (int)toY;

  if (this->tileMatrix.at(x).at(y).allowMovement(toX, toY, p)) {
    if ((int)fromX != x || (int)fromY != y) {
      this->tileMatrix.at((int)fromX).at((int)fromY).removePlayerFromTile(p);
      this->tileMatrix.at(x).at(y).addPlayer(p);
    }

    return true;
  }

  return false;
}

void Map::addPlayer(int x, int y, Player* p) {
  this->tileMatrix.at(x).at(y).addPlayer(p);
}

unsigned int Map::getAndIncreaseByOneNextUniqueItemId() {
  std::cout << Map::nextId << std::endl;
  Map::nextId++;
  return (Map::nextId - 1);
}