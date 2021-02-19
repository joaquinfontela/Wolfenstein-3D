//
// Created by joaquinfontela on 1/12/20.
//

#include "../../../includes/Model/Map/Map.h"

#include <iostream>
#include <tuple>



Map::Map(int dimx, int dimy) {
  this->nextId = 1;
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

void Map::setRespawnPoints(std::vector<Coordinate> respPoints){
  this->respawnPoints = respPoints;
}


bool Map::withinMap(int x, int y){
  return (x < this->dimx && y < this->dimy && x >= 0 && y >= 0);
}

void Map::applyDamageOnRadiusFrom(int damage, int x, int y, WaitingQueue<Notification*>& notif){

  int radius = 2;

  for(int i = x - radius; i < x + radius; i++){
    for(int j = y - radius; j < y + radius; j++){
      if(withinMap(i, j)){
        this->tileMatrix[i][j].applyDamageToPlayers(damage, abs(x-i) + abs(y-j), notif);
      }
    }
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

void Map::addAmmoDropAt(int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addAmmoDrop(this->getAndIncreaseByOneNextUniqueItemId());
}

void Map::addAmmoDropAt(int x, int y, WaitingQueue<Notification*>& notis) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addAmmoDrop(x, y, notis, this->getAndIncreaseByOneNextUniqueItemId());
}

void Map::addKeyDropAt(int x, int y) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addKeyDrop(this->getAndIncreaseByOneNextUniqueItemId());
}

void Map::addKeyDropAt(int x, int y, WaitingQueue<Notification*>& notis) {
  this->verifyCoordinateDoesNotSurpassMapLimits(x, y);
  this->tileMatrix[y - 1][x - 1].addKeyDrop(x, y, notis, this->getAndIncreaseByOneNextUniqueItemId());
}

void Map::verifyCoordinateDoesNotSurpassMapLimits(int x, int y) {
  if ((x > this->dimx) || (x < 1) || (y > this->dimy) || (y < 1))
    throw std::runtime_error(
        "Error adding item into map (map limits overpassed).");
}

bool Map::forceDoorStatusChange(int x, int y) {
  return this->tileMatrix.at(x).at(y).forceDoorStatusChange();
}

Player* Map::traceAttackFrom(Player* attacker, int range) {
  double initialX = attacker->getX();
  double initialY = attacker->getY();

  double dirX = attacker->getDirX() / 3.0;
  double dirY = attacker->getDirY() / 3.0;

  int i = 1;

  Player* p = nullptr;

  while (i < 1 + range) {
    double rayPosX = (initialX + i * dirX);
    double rayPosY = (initialY + i * dirY);

    int mapX = (int)rayPosX;
    int mapY = (int)rayPosY;

    if(!withinMap(mapX, mapY))
      return nullptr;

    if (this->tileMatrix.at(mapX).at(mapY).checkWall())
      return nullptr;

    else if ((p = this->tileMatrix.at(mapX).at(mapY).playerCollision(rayPosX, rayPosY, attacker)) != nullptr)
      return p;

    else if (((mapX + 1) - rayPosX) < 0.3 && ((mapX + 1) < this->dimx)) {
      if ((p = this->tileMatrix.at(mapX + 1).at(mapY).playerCollision(rayPosX, rayPosY, attacker)) != nullptr) {
        return p;
      }

    } else if (((mapY + 1) - rayPosY) < 0.3 && ((mapY + 1) < this->dimy)) {
      if ((p = this->tileMatrix.at(mapX).at(mapY + 1).playerCollision(rayPosX, rayPosY, attacker)) != nullptr) {
        return p;
      }
    } else if ((((mapY + 1) - rayPosY) < 0.3 && ((mapY + 1) < this->dimy)) && (((mapX + 1) - rayPosX) < 0.3 && ((mapX + 1) < this->dimx))) {
      if ((p = this->tileMatrix.at(mapX + 1).at(mapY + 1).playerCollision(rayPosX, rayPosY, attacker)) != nullptr) {
        return p;
      }
    }

    i++;
  }

  return p;
}

std::tuple<double, double> Map::handleRespawn() {
  bool randomTileHasPlayersInIt = true;
  Coordinate c;
  while (randomTileHasPlayersInIt) {
    c = this->getRandomRespawn();
    randomTileHasPlayersInIt = this->tileHasPlayers(c);
  }
  return std::make_tuple(c.getY() - 1, c.getX() - 1);
}

Coordinate Map::getRandomRespawn() {

  return this->respawnPoints.at(rand() % this->respawnPoints.size());
}

bool Map::tileHasPlayers(Coordinate& c) {
  return (this->tileMatrix[c.getY() - 1][c.getX() - 1].hasPlayers());
}

bool Map::moveTo(double fromX, double fromY, double toX, double toY, Player* p,
                 WaitingQueue<Notification*>& notis) {
  int x = (int)toX;
  int y = (int)toY;

  if(!withinMap(x, y))
    return false;

  if (this->tileMatrix.at(x).at(y).allowMovement(toX, toY, p, notis)) {
    if ((int)fromX != x || (int)fromY != y) {
      this->tileMatrix.at((int)fromX).at((int)fromY).removePlayerFromTile(p);
      this->tileMatrix.at(x).at(y).addPlayer(p);
    }

    return true;
  }

  return false;
}

bool Map::moveTo(double fromX, double fromY, double toX, double toY) {
  int x = (int)toX;
  int y = (int)toY;

  return this->tileMatrix.at(x).at(y).allowMovement(toX, toY);
}

void Map::addPlayer(int x, int y, Player* p) {
  this->tileMatrix.at(x).at(y).addPlayer(p);
}

unsigned int Map::getAndIncreaseByOneNextUniqueItemId() {
  nextId++;
  return (nextId - 1);
}

void Map::removePlayer(int x, int y, Player* p) {
  this->tileMatrix.at(x).at(y).removePlayerFromTile(p);
}

std::tuple<int, int> Map::moveDoor(Player* p) {
  double initialX = p->getX();
  double initialY = p->getY();
  double dirX = p->getDirX();
  double dirY = p->getDirY();

  int i = 1;
  double rayPosX = (initialX + i * dirX);
  double rayPosY = (initialY + i * dirY);

  int mapX = (int)rayPosX;
  int mapY = (int)rayPosY;

  if(!withinMap(mapX, mapY))
    return std::make_tuple(-1, -1);

  while (mapX == float(initialX) && mapY == float(initialY)) {
    rayPosX = (initialX + i * dirX);
    rayPosY = (initialY + i * dirY);

    mapX = (int)rayPosX;
    mapY = (int)rayPosY;

    i++;
  }

  if (this->tileMatrix.at(mapX).at(mapY).moveDoor(
          p))  // Temporal hasta que arregle el algoritmo de arriba.
    return std::make_tuple(mapX, mapY);
  else
    return std::make_tuple(-1, -1);
}
