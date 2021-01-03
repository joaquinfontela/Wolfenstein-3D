#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <string>
#include <vector>

#include "Tile/Tile.h"

#include "../Player/Player.h"

class Tile;
class Player;


typedef std::vector<std::vector<Tile>> TileMatrix;

class Map {
 public:
  Map(int dimx, int dimy);
  void addDropWithIdAt(int id, int x, int y);
  //std::vector<ItemDrop> getItemDropsAt(int x, int y);
  bool moveTo(double fromX, double fromY, double x, double y, Player* p);
  void verifyCoordinateDoesNotSurpassMapLimits(int x, int y);
  void addPlayer(int x, int y, Player* p);
  std::tuple<double, double> handleRespawn();
  Player* traceAttackFrom(Player* attacker);

 private:
  int dimx;
  int dimy;
  TileMatrix tileMatrix;
};

#endif  // TP_FINAL_MAP_H
