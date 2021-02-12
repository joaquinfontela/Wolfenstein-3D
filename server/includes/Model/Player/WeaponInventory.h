#ifndef __WEAPON_INVENTORY_H__
#define __WEAPON_INVENTORY_H__
#include "../Item/Weapon/Weapon.h"
#include "../Item/Weapon/WeaponFactory.h"
#include "PlayerConfig.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../Control/Notification/Notification.h"
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
  int getCurrentWeaponID();
  bool hasGunWithId(int uniqueId);
  void addWeapon(Weapon* weapon);
  void equipWeapon(int weaponPos);
  void pickUpAmmo();
  void dropAmmo();
  bool hasMaxAmmo();
  int attack(float timeElapsed, WaitingQueue<Notification*>& notis);
  int getRange();
  int getAmmo();
  int getShotsFired();
  bool wieldingNonAutomaticWeapon();
  ~WeaponInventory();
};




#endif
