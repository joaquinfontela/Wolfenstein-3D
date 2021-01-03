#ifndef __TILE_H__
#define __TILE_H__


#include <vector>

#include "../../Item/ItemDrop/ItemDrop.h"
#include "../../Player/Player.h"

class ItemDrop;

class Tile {
 private:
  int x;
  int y;
  bool isWall;
  std::vector<ItemDrop> drops;
  std::vector<Player*> players;

 public:
  Tile(int x, int y);
  void addDrop(ItemDrop itemDrop);
  void addDrop(int id);

  void addPlayer(Player* p);

  void removePlayerFromTile(Player* p);

  Player* playerCollision(double x, double y, Player* p);

  bool checkWall();
  std::vector<ItemDrop> getItemDrops();
  void setWall();
  bool allowMovement(double x, double y, Player* p);
};


#endif
