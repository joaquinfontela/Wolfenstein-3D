#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../../../common/includes/PlayerData.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../Control/Notification/Notification.h"
#include "../../Control/UpdatableEvent/Updatable.h"
#include "../Item/Weapon/Weapon.h"
#include "../Item/Weapon/WeaponFactory.h"
#include "../Map/Map.h"

class Map;
class Updatable;

/**
  * @section DESCRIPTION
  * Class that represents a player controlled by a user/client
  */

class Player {
 private:
  const unsigned int MAX_HEALTH, MAX_AMMO, BULLET_DROP_WHEN_DIES, AMMO_PICK_UP, POINTS_PER_KILL;
  double x, y;
  double dirX, dirY;
  double rotSpeed;
  double moveSpeed;

  int score;
  int kills;
  int shotsFired;

  unsigned int playerID;
  bool hasToBeNotified;
  unsigned int health, lifeRemaining, ammo;
  Weapon* currentWeapon;
  std::vector<Weapon*> weapons;
  bool key;
  bool shooting;
  bool isAdmin;
  WeaponFactory weaponFactory;
  Map& map;

  /*
   * [SERVER-SIDE] Handles the players death, and respawns to new position if possible
   *
   * @param Notification queue to notify if needed
   * @return 0 if respawn was possible, -1 otherwise
   */
  int handleDeath(WaitingQueue<Notification*>& notis);

 public:
   double planeX;
   double planeY;

  // CONSTRUCTORS
  Player(YAMLConfigReader yamlConfigReader, Map& map, unsigned int playerID);
  Player(YAMLConfigReader yamlConfigReader);

  /*
   * [SERVER-SIDE] Sets the shooting state as requested
   *
   * @param Boolean that represents if the player intends to shoot.
   *
   */
  void setShooting(bool state);

  /*
   * [SERVER-SIDE] Receives the indicated damage, if killed drops the required items and, if possible, respawns.
   *
   * @param Damage received
   * @param Queue of notifications on which to send, if required, new drops notification.
   *
   * @return 0 if killed and respawned, -1 if killed and unable to respawn. Remaining health otherwise.
   */
  int takeDamage(unsigned int damage, WaitingQueue<Notification*>& notis);

  /*
   * [SERVER-SIDE] Sets the notifiable status as requested.
   *
   * @param The status to set.
   */
  void setNotifiable(bool status);

  // GETTERS
  unsigned int ID();
  double getX();
  double getY();
  double getDirX();
  double getDirY();
  int getKills();
  int getShotsFired();
  void setAdmin();
  int getScore();

  /*
   * [SERVER-SIDE] Indicates if the player has admin rights over the game
   *
   * @return True if players has admin rights, false otherwise.
   */
  bool hasAdmin();

  /*
   * [SERVER-SIDE] Adds the indicated weapon to the inventory.
   *
   * @param The weapon to add to the inventory
   */
  void addWeapon(Weapon* weapon);

  /*
   * [SERVER-SIDE] Indicates if the player has a gun with indicated ID
   *
   * @param ID of the gun to check on the players inventory.
   *
   * @return True if the player has that weapon, false otherwiwse.
   */
  bool hasGunWithId(int uniqueId);

  /*
   * [SERVER-SIDE] Respawns the player onto a new position on the map.
   *
   * @param The notification Queue on which to send notification if required.
   */
  void respawn(WaitingQueue<Notification*>& notis);

  /*
   * [SERVER-SIDE] Calculates distance to another specified player.
   *
   * @param The other player to calculate the distance
   *
   * @return The distance to that player, as a double value.
  double calculateDistanceTo(Player* other);

  /*
   * [SERVER-SIDE] Fills the struct PlayerData with the appropiate values for this player
   *
   * @param The struct on which to set the data
   */
  void fillPlayerData(PlayerData& data);

  /*
   * [SERVER-SIDE] If possible, shoots the current weapon of the player.
   *
   * @param Time elapsed since last server update.
   *
   * @return Damage the player would inflict if the bullet hits.
   */
  int attack(float timeElapsed);

  /*
   * [SERVER-SIDE] Shoots, if possible, current weapon and applies damage if required.
   *
   * @param Time elapsed since last server update.
   * @param Notification Queue on which to notify of any events if required
   * @param Updatables list if player shoots an updatable weapon.
   */
  void shoot(float timeElapsed, WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables);

  /*
   * [SERVER-SIDE] Shoots the RPG, creating an instance of an updatable rocket.
   *
   * @param The notification queue on which to notify if required
   * @param Updatables list to push the new instance of Rocket.
   */
  void shootRPG(WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables);

  /*
   * [SERVER-SIDE] Updates the movement speed of the player by the specified value
   *
   * @param The movement speed to add to the player
   */
  void updateMoveSpeed(double movSpeed);

   /*
   * [SERVER-SIDE] Updates the rotation speed of the player by the specified value
   *
   * @param The rotation speed to add to the player
   */
  void updateRotationSpeed(double rotSpeed);

  /*
   * [SERVER-SIDE] Moves the player to the specfied coordinate (x, y)
   *
   * @param X Coordinate
   * @param Y Coordinate
   */
  void moveTo(double x, double y);

  /*
   * [SERVER-SIDE] Return the range the current weapon of the player has.
   *
   * @return The range of the current weapon
   */
  int getRange();

  /*
   * [SERVER-SIDE] Switches the active weapon to the specified slot
   *
   * @param The slot to set as active
   */
  void equipWeapon(int weaponPos);

  /*
   * [SERVER-SIDE] Checks collision with a coordinate (x, y)
   *
   * @param X Coordinate
   * @param Y Coordinate
   *
   * @return True if the collision occured, false otherwise.
   */
  bool collidesWith(double x, double y);

  /*
   * [SERVER-SIDE] Checks if the player has to be updated
   *
   * @return True if the player has to be updated, false otherwise.
  bool hasToBeUpdated();

  /*
   * [SERVER-SIDE] Updates, if required, position and shooting status of the current player
   *
   * @param Time elapsed since last update
   * @param Notification queue on which to push new notifications
   * @param Updatable list to push new updatables event if required
   */
  void update(float timeElapsed, WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables);

  /*
   * [SERVER-SIDE] Pick ups key, setting key status to true
   */
  void pickupKey();

  /*
   * [SERVER-SIDE] Checks if player has a key
   *
   * @return True if player has a key, false otherwise.
   */
  bool hasKey();

  /*
   * [SERVER-SIDE] Checks if player has max ammo
   *
   * @return True if player has max ammo, false otherwise.
   */
  bool hasMaxAmmo();

  /*
   * [SERVER-SIDE] Pick ups ammo, adding to existing amount up to specified limit.
   */
  void pickUpAmmo();

  /*
   * [SERVER-SIDE] Gives current health of the player.
   *
   * @return The health of the player
   */
  int getHealth();

  /*
   * [SERVER-SIDE] Checks if the player has max health.
   *
   * @return True if the player has max health, false otherwise
   */
  bool hasFullHealth();

  /*
   * [SERVER-SIDE] Adds health onto the players health pool.
   *
   * @param The health to add.
   */
  void addHealth(int health);

   /*
   * [SERVER-SIDE] Adds points to the player.
   *
   * @param The points to add.
   */
  void addPoints(int points);

  double calculateDistanceTo(Player* p);

  bool hasToBeUpdated();


  ~Player();
};

#endif
