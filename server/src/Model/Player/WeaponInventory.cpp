#include "../../../includes/Model/Player/WeaponInventory.h"
#include "../../../includes/Control/Notification/ShotsFired.h"
#include <iostream>

WeaponInventory::WeaponInventory(PlayerConfig& config, int playerID) : config(config), playerID(playerID){

  this->ammo = config.AMMO_AT_START;
  this->shotsFired = 0;

  // Puedo inicializar estas armas con un -1 como ID de esa unidad dado que cuchillos y pistolas no se encuentran en el piso.
  this->weapons.push_back(weaponFactory.getWeapon(1, -1));
  this->weapons.push_back(weaponFactory.getWeapon(2, -1));

  this->currentWeapon = this->weapons.at(1);
}

bool WeaponInventory::hasGunWithId(int uniqueId){
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  for (; it != this->weapons.end(); ++it) {
    if ((*it)->getID() == uniqueId) return true;
  }

  return false;
}

void WeaponInventory::addWeapon(Weapon* weapon){
  this->weapons.push_back(weapon);
}

int WeaponInventory::getAmmo(){
  return this->ammo;
}

int WeaponInventory::getShotsFired(){
  return this->shotsFired;
}

void WeaponInventory::pickUpAmmo(){
  if (this->ammo == 0)
    this->currentWeapon = this->weapons.at(1);

  ammo += config.AMMO_PICK_UP;
  if (ammo > config.MAX_AMMO)
    ammo = config.MAX_AMMO;
}

bool WeaponInventory::hasMaxAmmo(){
  return this->ammo == config.MAX_AMMO;
}

bool WeaponInventory::wieldingNonAutomaticWeapon(){
  return (this->currentWeapon->getID() == 1 || this->currentWeapon->getID() == 2 || this->currentWeapon->getID() == 5);
}

int WeaponInventory::getCurrentWeaponID(){
  return this->currentWeapon->getID();
}

void WeaponInventory::dropAmmo(){
  if(this->ammo <= config.BULLET_DROP_WHEN_DIES)
    this->ammo = 0;
  else
    this->ammo -= config.BULLET_DROP_WHEN_DIES;

}

void WeaponInventory::equipWeapon(int weaponPos){
  if ((weaponPos >= this->weapons.size()) || (this->ammo <= 0)) return;

  this->currentWeapon = this->weapons.at(weaponPos);
}

int WeaponInventory::getRange(){
  return this->currentWeapon->getRange();
}

int WeaponInventory::attack(float timeElapsed, WaitingQueue<Notification*>& notis){
  int ammo = this->ammo;
  int damageDealt = this->currentWeapon->attack(ammo, timeElapsed);
  this->shotsFired += (this->ammo - ammo);
  this->ammo = ammo;

  if(damageDealt != -1){ // Efectivamente se efectuó un disparo.
    ShotsFired* noti = new ShotsFired(this->playerID);
    notis.push(noti);
  }

  if (this->ammo <= 0) {
    this->currentWeapon = this->weapons.at(0);
  }

  return damageDealt;
}

WeaponInventory::~WeaponInventory(){
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  for (; it != this->weapons.end(); ++it) {
    delete (*it);
  }
}
