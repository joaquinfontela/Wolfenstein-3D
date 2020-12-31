#include "../../../includes/Map/Tile/Tile.h"

Tile::Tile(int x, int y) {
  this->x = x;
  this->y = y;
}

void Tile::addDrop(int id) {
  ItemDrop i(id);
  drops.push_back(i);
}

std::vector<ItemDrop> Tile::getItemDrops() { return drops; }