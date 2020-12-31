#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <string>
#include <vector>

#include "./Tile/Tile.h"

typedef std::vector<std::vector<Tile>> TileMatrix;

class Map {
 public:
  Map(int dimx, int dimy);
  void addDropWithIdAt(int id, int x, int y);
  std::vector<ItemDrop> getItemDropsAt(int x, int y);

 private:
  int dimx;
  int dimy;
  TileMatrix tileMatrix;
};

#endif  // TP_FINAL_MAP_H
