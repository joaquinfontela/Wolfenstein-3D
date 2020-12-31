#include "../../../includes/Map/Tile/Tile.h"

Tile::Tile(int x, int y) {
  this->x = x;
  this->y = y;
}

void Tile::addDrop(int id) { dropsIds.push_back(id); }

std::vector<int> Tile::getDropIds() { return dropsIds; }