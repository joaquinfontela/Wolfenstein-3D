#ifndef __TILE_H__
#define __TILE_H__

#include <vector>

#include "../../../../../common/includes/Queue/WaitingQueue.h"
#include "../../../Control/Notification/Notification.h"
#include "../../../Control/Notification/PlayerPickUpItem.h"
#include "../../../Control/Notification/PlayerDropItem.h"
#include "../../Door/Door.h"
#include "../../Item/Item.h"
#include "../../Item/Weapon/Weapon.h"
#include "../../Player/Player.h"
#include "../../Wall/BlueWall.h"
#include "../../Wall/Wall.h"
#include "../Map.h"

class Player;
class Item;

class Tile {
 private:
  Door* door;
  Wall* wall;
  std::vector<Player*> players;
  std::vector<Item*> items;
  std::vector<Weapon*> weapons;
  bool isWall();
  void deleteDoor();
  void deleteWall();
  void deleteItemDrops();
  void deleteWeaponDrops();

 public:
  Tile();
  void addItemDrop(Item* item);
  void addWeaponDrop(Weapon* weapon);
  void addDoor(Door* door);
  void addWall(Wall* wall);

  void addAmmoDrop(int uniqueId);
  void addKeyDrop(int uniqueId);

  void addAmmoDrop(int x, int y, WaitingQueue<Notification*>& notis, int uniqueId);
  void addKeyDrop(int x, int y, WaitingQueue<Notification*>& notis, int uniqueId);

  // Guns within the Tile will be added to the Players inventory if he does not
  // currently own the weapon.
  void pickUpGuns(Player* p, WaitingQueue<Notification*>& notis);

  // Changes the door status within the Tile if it exists and if possible.
  // Returns true if the door was succesfully opened.
  bool moveDoor(Player* p);

  void applyDamageToPlayers(int damage, int distanceToCenter, WaitingQueue<Notification*>& notif);

  // Agrega un jugador al Tile.
  void addPlayer(Player* p);

  void pickUpItems(double x, double y, Player* p,
                   WaitingQueue<Notification*>& notis);

  // Remueve el jugador del Tile.
  void removePlayerFromTile(Player* p);

  bool forceDoorStatusChange();

  // Devuelve el primer jugador con el que colisiona el punto (x, y). Nullptr si
  // no existe tal jugador.
  Player* playerCollision(double x, double y, Player* p);

  // Devuelve True si la celda es una pared.
  bool checkWall();

  // Setea la celda como pared y colisionable.
  void setWall();

  // Devuelve true si autoriza el movimiento de un jugador a la posicion (x, y)
  bool allowMovement(double x, double y, Player* p,
                     WaitingQueue<Notification*>& notis);

  // Devuelve true si autoriza el movimiento de un elemento posicionable a la posicion (x, y)
  bool allowMovement(double x, double y);



  bool hasPlayers();

  ~Tile();
};

#endif
