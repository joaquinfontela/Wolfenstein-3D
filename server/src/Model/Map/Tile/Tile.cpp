#include "../../../../includes/Model/Map/Tile/Tile.h"

Tile::Tile(int x, int y) {
  this->x = x;
  this->y = y;
  this->isWall = false;
}

void Tile::addDrop(int id) {
  ItemDrop i(id);
  drops.push_back(i);
}

std::vector<ItemDrop> Tile::getItemDrops() { return drops; }


bool Tile::allowMovement(){
  return !this->isWall; // Faltaria chequear la interseccion con los jugadores.
}

void Tile::setWall(){
  this->isWall = true;
}
