#include "../../../includes/Map/Tile/Tile.h"

Tile::Tile(int x, int y) {
  this->x = x;
  this->y = y;
}

void Tile::addDrop(int id){}
void Tile::addDrop(ItemDrop itemDrop) { drops.push_back(itemDrop); }

std::vector<ItemDrop> Tile::getItemDrops() { return drops; }
