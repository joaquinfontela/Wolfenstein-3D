#ifndef __TILE_H__
#define __TILE_H__

#include <vector>

#include "../../Item/Item.h"
#include "../../Item/Weapon/Weapon.h"
#include "../../Player/Player.h"

class Player;
class Item;

class Tile {
 private:
  bool isWall;
  std::vector<Player*> players;
  std::vector<Item*> items;
  std::vector<Weapon*> weapons;

 public:
  Tile();
  void addItemDrop(Item* item);
  void addWeaponDrop(Weapon* weapon);

  // Agrega un jugador al Tile.
  void addPlayer(Player* p);

  // Remueve el jugador del Tile.
  void removePlayerFromTile(Player* p);

  // Devuelve el primer jugador con el que colisiona el punto (x, y). Nullptr si
  // no existe tal jugador.
  Player* playerCollision(double x, double y, Player* p);

  // Devuelve True si la celda es una pared.
  bool checkWall();

  // Setea la celda como pared y colisionable.
  void setWall();

  // Devuelve true si autoriza el movimiento de un jugador a la posicion (x, y)
  bool allowMovement(double x, double y, Player* p);
};

#endif
