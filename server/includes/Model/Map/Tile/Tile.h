#ifndef __TILE_H__
#define __TILE_H__


#include <vector>


#include "../../Player/Player.h"

class Player;

class Tile {
 private:
  int x;
  int y;
  bool isWall;
  //std::vector<ItemDrop> drops;
  std::vector<Player*> players;

 public:
  Tile(int x, int y);
  //void addDrop(ItemDrop itemDrop);
  void addDrop(int id);

  // Agrega un jugador al Tile.
  void addPlayer(Player* p);

  // Remueve el jugador del Tile.
  void removePlayerFromTile(Player* p);

  // Devuelve el primer jugador con el que colisiona el punto (x, y). Nullptr si no existe tal jugador.
  Player* playerCollision(double x, double y, Player* p);

  // Devuelve True si la celda es una pared.
  bool checkWall();
  //std::vector<ItemDrop> getItemDrops();

  // Setea la celda como pared y colisionable.
  void setWall();

  // Devuelve true si autoriza el movimiento de un jugador a la posicion (x, y)
  bool allowMovement(double x, double y, Player* p);
};


#endif
