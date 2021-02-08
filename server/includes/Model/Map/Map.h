#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <cstdlib>
#include <string>
#include <vector>

#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../../../common/includes/YAML/YAMLMapReader.h"
#include "../../Control/Notification/Notification.h"
#include "../Player/Player.h"
#include "Tile/Tile.h"

/*
 * [SERVER-SIDE] Class that represents the map the players can interact with
 *
 */

class Tile;
class Player;
class Item;
class Wall;
class Weapon;

typedef std::vector<std::vector<Tile>> TileMatrix;

class Map {
 public:
  Map(int dimx, int dimy);

  /*
   * [SERVER-SIDE] Adds an item drop at specified location
   *
   * @param Item to add
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addItemDropAt(Item* item, int x, int y);

  /*
   * [SERVER-SIDE] Adds a weapon drop at specified location
   *
   * @param Weapon to add
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addWeaponDropAt(Weapon* weapon, int x, int y);

  /*
   * [SERVER-SIDE] Adds a door at specified location
   *
   * @param Door to add
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addDoorAt(Door* door, int x, int y);

  /*
   * [SERVER-SIDE] Adds wall at specified location
   *
   * @param Wall to add
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addWallAt(Wall* wall, int x, int y);

  /*
   * [SERVER-SIDE] Adds ammo at specified location
   *
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addAmmoDropAt(int x, int y);

  /*
   * [SERVER-SIDE] Adds key at specified location
   *
   * @param X Coordinate
   * @param Y Coordinate
   */
  void addKeyDropAt(int x, int y);

  /*
   * [SERVER-SIDE] Adds ammo at specified location and notifies it
   *
   * @param X Coordinate
   * @param Y Coordinate
   * @param Notification Queue
   */
  void addAmmoDropAt(int x, int y, WaitingQueue<Notification*>& notis);

  /*
   * [SERVER-SIDE] Adds key at specified location and notifies it
   *
   * @param X Coordinate
   * @param Y Coordinate
   * @param Notification Queue
   */
  void addKeyDropAt(int x, int y, WaitingQueue<Notification*>& notis);

  /*
   * [SERVER-SIDE] Removes player from position
   *
   * @param X Coordinate
   * @param Y Coordinate
   * @param Player to remove
   */
  void removePlayer(int x, int y, Player* p);

  /*
   * [SERVER-SIDE] Forces door status to change on specified location
   *
   * @param X Coordinate
   * @param Y Coordinate
   *
   * @return Boolean indicating if change was possible
   */
  bool forceDoorStatusChange(int x, int y);

  /*
   * [SERVER-SIDE] Sets the maps respawn points
   *
   * @param Vector containing respawn point coordinates
   */
  void setRespawnPoints(std::vector<Coordinate> respPoints);

  /*
   * [SERVER-SIDE] Applies damage to all players within radius of a certain
   * center
   *
   * @param Damage to apply
   * @param X Coordinate
   * @param Y Coordinate
   * @param Notification Queue to notify if needed
   */
  void applyDamageOnRadiusFrom(int damage, int x, int y,
                               WaitingQueue<Notification*>& notif);

  /*
   * [SERVER-SIDE] Moves player from one location to another
   *
   * @param Initial X Coordinate
   * @param Initial Y Coordinate
   * @param Desired X Coordinate
   * @param Desired Y Coordinate
   * @param Player intending the move
   * @param Notification queue to notify if needed
   *
   * @return Boolean indicating if move was possible
   */
  bool moveTo(double fromX, double fromY, double x, double y, Player* p,
              WaitingQueue<Notification*>& notis);

  /*
   * [SERVER-SIDE] Checks if Coordinate is within map boundaries
   *
   * @param X Coordinate
   * @param Y Coordinate
   *
   * @return True if within boundaries, false otherwise
   */
  bool withinMap(int x, int y);

  /*
   * [SERVER-SIDE] Moves item from one position to another, without the
   * possibilty of notify of changes
   *
   * @param Initial X Coordinate
   * @param Initial Y Coordinate
   * @param Final X Coordinate
   * @param Final Y Coordinate
   *
   * @return True if move was possible, false otherwise
   */
  bool moveTo(double fromX, double fromY, double x, double y);

  /*
   * [SERVER-SIDE] Same as within map, redundant.
   */
  void verifyCoordinateDoesNotSurpassMapLimits(int x, int y);

  /*
   * [SERVER-SIDE] Adds player onto map
   *
   * @param X Coordinate
   * @param Y Coordinate
   * @param Player to add
   */
  void addPlayer(int x, int y, Player* p);

  /*
   * [SERVER-SIDE] Sets respawn point for player
   *
   * @return Tuple indicating Respawn (X, Y) Coordinates
   */
  std::tuple<double, double> handleRespawn();

  /*
   * [SERVER-SIDE] If possible, moves the door the player is facing
   *
   * @param Player intending to make the move
   *
   * @return Coordinate of changed door, (-1, -1) otherwise
   */
  std::tuple<int, int> moveDoor(Player* p);

  /*
   * [SERVER-SIDE] Traces a bullet from the player and checks for collisions
   *
   * @param Player making the shot
   * @param Range of the shot
   *
   * @return First hit player, nullptr otherwise. (Maybe consider using
   * std::optional?)
   */
  Player* traceAttackFrom(Player* attacker, int range);

  /*
   * [SERVER-SIDE] Static method, increases the unique id counter for all items
   * on the map and return the new id
   *
   * @return The unique ID the new item should use
   */
  unsigned int getAndIncreaseByOneNextUniqueItemId();

 private:
  unsigned int nextId;
  std::vector<Coordinate> respawnPoints;
  int dimx;
  int dimy;
  TileMatrix tileMatrix;
  Coordinate getRandomRespawn();
  bool tileHasPlayers(Coordinate& c);
};

#endif  // TP_FINAL_MAP_H
