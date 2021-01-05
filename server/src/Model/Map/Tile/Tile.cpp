#include "../../../../includes/Model/Map/Tile/Tile.h"

Tile::Tile() { this->isWall = false; }

void Tile::addItemDrop(Item* item) { items.push_back(item); }

void Tile::addWeaponDrop(Weapon* weapon) { weapons.push_back(weapon); }

// std::vector<ItemDrop> Tile::getItemDrops() { return drops; }

bool Tile::allowMovement(double x, double y, Player* p) {
  if (this->isWall) return false;

  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) continue;

    if ((*it)->collidesWith(x, y)) return false;
  }

  return true;  // Faltaria chequear la interseccion con los jugadores.
}

bool Tile::checkWall() { return this->isWall; }

Player* Tile::playerCollision(double x, double y, Player* p) {
  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it)->collidesWith(x, y) && (*it) != p) return (*it);
  }

  return nullptr;
}
void Tile::addPlayer(Player* p) { this->players.push_back(p); }
void Tile::setWall() { this->isWall = true; }

void Tile::removePlayerFromTile(Player* p) {
  std::vector<Player*>::iterator it = this->players.begin();

  for (; it != this->players.end(); ++it) {
    if ((*it) == p) {
      this->players.erase(it);
      break;
    }
  }
}
