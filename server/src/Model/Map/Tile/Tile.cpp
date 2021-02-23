#include "../../../../includes/Model/Map/Tile/Tile.h"

#include <iostream>

#include "../../../../includes/Model/Item/Ammo.h"
#include "../../../../includes/Model/Item/Key.h"

Tile::Tile() {
  this->door = nullptr;
  this->wall = nullptr;
}

bool Tile::isWall() {
  return (this->wall != nullptr) ||
         (this->door != nullptr && this->door->isLocked());
}

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

void Tile::addAmmoDrop(int uniqueId) {
  this->items.push_back(new Ammo(101, uniqueId));
  this->deleteDoor();
  this->deleteWall();
}

void Tile::addKeyDrop(int uniqueId) {
  this->items.push_back(new Key(108, uniqueId));
  this->deleteDoor();
  this->deleteWall();
}

void Tile::addKeyDrop(int x, int y, WaitingQueue<Notification*>& notis, int uniqueId) {

  this->items.push_back(new Key(108, uniqueId));
  PlayerDropItem* noti = new PlayerDropItem(x, y, 108, uniqueId);
  notis.push(noti);

  this->deleteDoor();
  this->deleteWall();
}

void Tile::addAmmoDrop(int x, int y, WaitingQueue<Notification*>& notis, int uniqueId) {

  this->items.push_back(new Ammo(101, uniqueId));

  PlayerDropItem* noti = new PlayerDropItem(x, y, 101, uniqueId);
  notis.push(noti);
  this->deleteDoor();
  this->deleteWall();
}

void Tile::applyDamageToPlayers(int damage, int distanceToCenter, WaitingQueue<Notification*>& notif){
  if(this->isWall())
    return;

  std::vector<Player*>::iterator it = this->players.begin();

  while(it != this->players.end()){
    unsigned int remainingHealth = (*it)->takeDamage(damage, notif);
    if(remainingHealth == 0 || remainingHealth == -1)
      continue;
    else
      ++it;
  }
}



bool Tile::forceDoorStatusChange() {
  if (this->door && this->players.size() == 0) { // Para que no cierre la puerta mientras haya un jugador adentro de su celda.
    this->door->changeStatus();
    return true;
  }

  if (!this->door) return true;

  return false;
}

void Tile::pickUpItems(double x, double y, Player* p,
                       WaitingQueue<Notification*>& notis) {
  // Por ahora hago que agarre todos los que estan en la misma celda, en
  // realidad el item deberia tener un hitbox y deberia preguntarle a cada uno
  // si estoy en rango para agarrarlo.
  std::vector<Item*>::iterator it = this->items.begin();

  while (it != this->items.end()) {
    if ((*it)->canBePickedUpBy(p)) {
      PlayerPickupItem* noti = new PlayerPickupItem((*it)->getID());
      notis.push(noti);
      (*it)->pickUp(p);
      delete *it;
      it = this->items.erase(it);
    } else {
      ++it;
    }
  }
}

bool Tile::allowMovement(double x, double y, Player* p,
                         WaitingQueue<Notification*>& notis) {
  if (this->isWall()) return false;

  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) continue;

    if ((*it)->collidesWith(x, y)) return false;
  }

  // Se autorizo el movimiento, asique veo que items hay en su posicion por si
  // tengo que agarrar alguno.

  pickUpItems(x, y, p, notis);
  pickUpGuns(p, notis);

  return true;
}

bool Tile::allowMovement(double x, double y) {
    if (this->isWall()){
       return false;
    }

    std::vector<Player*>::iterator it = this->players.begin();

    for (; it != this->players.end(); ++it) {
      if ((*it)->collidesWith(x, y)){
        return false;
      }
    }

  return true;
}

void Tile::pickUpGuns(Player* p, WaitingQueue<Notification*>& notis) {
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  while (it != this->weapons.end()) {
    if (p->hasGunWithId((*it)->getID())) {
      ++it;
    } else {
      p->addWeapon((*it));
      PlayerPickupItem* noti = new PlayerPickupItem((*it)->getUniqueId());
      notis.push(noti);
      it = this->weapons.erase(it);
    }
  }
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

bool Tile::moveDoor(Player* p) {
  if (this->door == nullptr) {
    return false;
  }

  return this->door->unlock(p->hasKey());
}

bool Tile::hasPlayers() {
  return ((!this->players.empty()) && (this->wall == nullptr) && (this->door == nullptr));
  }

Tile::~Tile() {
  this->deleteWeaponDrops();
  this->deleteItemDrops();
  this->deleteDoor();
  this->deleteWall();
}
