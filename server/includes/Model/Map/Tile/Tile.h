#ifndef __TILE_H__
#define __TILE_H__


#include <vector>

#include "../../Item/ItemDrop/ItemDrop.h"

class ItemDrop;

class Tile {
 private:
  int x;
  int y;
  bool isWall;
  std::vector<ItemDrop> drops;

 public:
  Tile(int x, int y);
  void addDrop(int id);
  std::vector<ItemDrop> getItemDrops();
  void setWall();
  bool allowMovement();
};


#endif
