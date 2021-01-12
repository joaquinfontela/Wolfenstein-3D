#include "../../../../includes/Model/Map/Tile/Tile.h"

#include <iostream>

#include "../../../../includes/Model/Item/Ammo.h"
#include "../../../../includes/Model/Item/Key.h"

Tile::Tile() {
  this->door = nullptr;
  this->wall = nullptr;
}

bool Tile::isWall() {

  return (this->wall != nullptr) || (this->door != nullptr && this->door->isLocked()); }

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

void Tile::addAmmoDrop() {
  this->items.push_back(new Ammo(Map::getAndIncreaseByOneNextUniqueItemId()));
  this->deleteDoor();
  this->deleteWall();
}

void Tile::addKeyDrop() {
  this->items.push_back(new Key(Map::getAndIncreaseByOneNextUniqueItemId()));
  this->deleteDoor();
  this->deleteWall();
}

void Tile::pickUpItems(double x, double y, Player* p) {
  // Por ahora hago que agarre todos los que estan en la misma celda, en
  // realidad el item deberia tener un hitbox y deberia preguntarle a cada uno
  // si estoy en rango para agarrarlo.
  std::vector<Item*>::iterator it = this->items.begin();

  while (it != this->items.end()) {
    if ((*it)->canBePickedUpBy(p)) {
      std::cout << "Player picking up item." << std::endl;
      (*it)->pickUp(p);
      delete *it;
      it = this->items.erase(it);
    } else {
      std::cout << "Player could not pick up item" << std::endl;
      ++it;
    }
  }
}

bool Tile::allowMovement(double x, double y, Player* p) {
  if (this->isWall()) return false;

  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) continue;

    if ((*it)->collidesWith(x, y)) return false;
  }

  // Se autorizo el movimiento, asique veo que items hay en su posicion por si
  // tengo que agarrar alguno.

  pickUpItems(x, y, p);
  return true;
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

bool Tile::moveDoor(Player* p){

  if(this->door == nullptr){
    return false;
  }

  return this->door->unlock(p);
}

Tile::~Tile() {
  this->deleteWeaponDrops();
  this->deleteItemDrops();
  this->deleteDoor();
  this->deleteWall();
}
