#include "../../../../includes/Model/Map/Tile/Tile.h"

Tile::Tile() {}

bool Tile::isWall() { return (this->wall != nullptr); }

void Tile::deleteDoor() {
  delete this->door;
  this->door = nullptr;
}

void Tile::deleteWall() {
  delete this->wall;
  this->wall = nullptr;
}

void Tile::deleteItemDrops() {
  for (Item* i : items) delete i;
  items.clear();
}

void Tile::deleteWeaponDrops() {
  for (Weapon* w : weapons) delete w;
  weapons.clear();
}

void Tile::addItemDrop(Item* item) {
  items.push_back(item);
  this->deleteDoor();
  this->deleteWall();
}

void Tile::addWeaponDrop(Weapon* weapon) {
  weapons.push_back(weapon);
  this->deleteDoor();
  this->deleteWall();
}

void Tile::addDoor(Door* door) {
  this->door = door;
  this->deleteWall();
  this->deleteItemDrops();
  this->deleteWeaponDrops();
}

void Tile::addWall(Wall* wall) {
  this->wall = wall;
  this->deleteDoor();
  this->deleteItemDrops();
  this->deleteWeaponDrops();
}

bool Tile::allowMovement(double x, double y, Player* p) {
  if (this->isWall()) return false;

  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) continue;

    if ((*it)->collidesWith(x, y)) return false;
  }

  return true;  // Faltaria chequear la interseccion con los jugadores.
}

bool Tile::checkWall() { return this->isWall(); }

Player* Tile::playerCollision(double x, double y, Player* p) {
  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it)->collidesWith(x, y) && (*it) != p) return (*it);
  }

  return nullptr;
}
void Tile::addPlayer(Player* p) { this->players.push_back(p); }

void Tile::setWall() {
  this->wall = new Wall(true);  // por ahora, despues este metodo se elimina
}

void Tile::removePlayerFromTile(Player* p) {
  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) {
      this->players.erase(it);
      break;
    }
  }
}
