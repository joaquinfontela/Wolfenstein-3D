#ifndef __WEAPON_INVENTORY_H__
#define __WEAPON_INVENTORY_H__
#include "../Item/Weapon/Weapon.h"
#include "../Item/Weapon/WeaponFactory.h"
#include "PlayerConfig.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../Control/Notification/Notification.h"

/*
 * @section DESCRIPTION
 * Class that represents the inventory of weapons of a player, managing shots fired and damage dealt.
 */
 
class WeaponInventory{

private:
  PlayerConfig& config;
  Weapon* currentWeapon;
  std::vector<Weapon*> weapons;
  WeaponFactory weaponFactory;
  int ammo;
  int playerID;
  int shotsFired;

public:

  WeaponInventory(PlayerConfig& config, int playerID);

  /*
   * @brief Return the current ID of the active weapons
   *
   * @return The ID of the active weapon.
   */
  int getCurrentWeaponID();

  /*
   * @brief Checks if a weapon with that uniqueId is in the inventory.
   *
   * @param The weapon ID
   * @return True if the weapon is in the inventory, false otherwise
   */
  bool hasGunWithId(int uniqueId);

  /*
   * @brief Adds the given weapon to the inventory
   *
   * @param The weapon to add
   */
  void addWeapon(Weapon* weapon);

  /*
   * @brief Equips the weapon in the specified slot. If weaponPos > inventorySize, nothing happens.
   *
   * @param The position on the inventory
   */
  void equipWeapon(int weaponPos);

  /*
   * @brief Picks up ammunition
   *
   */
  void pickUpAmmo();

  /*
   * @brief Drops ammunition
   *
   */
  void dropAmmo();

  /*
   * @brief Checks if the player has max ammunition.
   *
   * @return True if player has max ammo, false otherwise.
   */
  bool hasMaxAmmo();

  /*
   * @brief Attacks with current weapon, returning damage dealt.
   *
   * @param Time elapsed since last update
   * @param Notification queue to notify of changes
   *
   * @return damage dealt by current weapon, -1 if error.
   */
  int attack(float timeElapsed, WaitingQueue<Notification*>& notis);

  /*
   * @brief Returns range of equiped weapon.
   *
   * @return Range of the weapon.
   */
  int getRange();

  /*
   * @brief Returns the current amount of ammo
   *
   * @return Current amount of ammo.
   */
  int getAmmo();

  /*
   * @brief Returns the amount of shots fired by the user
   *
   * @return Amount of shots fired by user.
   */
  int getShotsFired();

  /*
   * @brief Checks if player has a Non-Automatic weapon equiped.
   *
   * @return True if equiped with Non-Automatic weapon, false otherwise.
   */
  bool wieldingNonAutomaticWeapon();
  ~WeaponInventory();
};




#endif
