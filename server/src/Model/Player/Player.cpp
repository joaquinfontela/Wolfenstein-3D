#include "../../../includes/Model/Player/Player.h"

#include <math.h>

#include <functional>
#include <iostream>
#include <tuple>

#include "../../../includes/Model/Item/Weapon/Knife.h"
#include "../../../includes/Model/Item/Weapon/Shootable/Pistol.h"
#include "../../../includes/Model/Item/Weapon/Weapon.h"
#include "../../../includes/Control/Notification/PlayerDied.h"
#include "../../../includes/Control/Notification/ShotsFired.h"
#include "../../../includes/Control/Notification/PlayerDisconnect.h"
#include "../../../includes/Control/UpdatableEvent/RocketMissile.h"

Player::Player(YAMLConfigReader yamlConfigReader, Map& map, unsigned int playerID) : config(yamlConfigReader), map(map) {

  this->health = config.MAX_HEALTH;
  this->lifeRemaining = config.MAX_RESPAWN;
  this->ammo = config.AMMO_AT_START;
  this->key = false;
  this->score = 0;
  this->hasToBeNotified = false;
  this->playerID = playerID;
  this->shooting = false;
  this->isAdmin = false;
  this->dead = false;
  this->kills = 0;
  this->shotsFired = 0;
  this->position = new Position(this, this->map);
  weapons.push_back(weaponFactory.getWeapon(1, map.getAndIncreaseByOneNextUniqueItemId()));
  weapons.push_back(weaponFactory.getWeapon(2, map.getAndIncreaseByOneNextUniqueItemId()));
  this->currentWeapon = weapons.at(1);
}

bool Player::isDead(){
  return this->dead;
}

void Player::setAdmin(){
  isAdmin = true;
}

bool Player::hasAdmin(){
  return isAdmin;
}

void Player::setShooting(bool state){
  this->shooting = state;
  this->hasToBeNotified = true;
}

bool Player::hasGunWithId(int uniqueId) {
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  for (; it != this->weapons.end(); ++it) {
    if ((*it)->getID() == uniqueId) return true;
  }

  return false;
}

void Player::addWeapon(Weapon* weapon) {
  this->weapons.push_back(weapon);
}

bool Player::collidesWith(double x, double y) {
  return this->position->collidesWith(x, y);
}

int Player::processFinalDeath(WaitingQueue<Notification*>& notis){
  this->map.removePlayer(int(this->position->getX()), int(this->position->getX()), this);

  PlayerDisconnect* disconnect = new PlayerDisconnect(this->playerID);
  notis.push(disconnect);

  this->dead = true;
  this->health = 0;
  return -1;
}

int Player::handleDeath(WaitingQueue<Notification*>& notis) {
  PlayerDied* noti = new PlayerDied(this->playerID);
  notis.push(noti);
  map.addAmmoDropAt(this->position->getY() + 1, this->position->getX() + 1, notis);
  if (this->key) {
    this->key = false;
    map.addKeyDropAt(this->position->getY() + 1, this->position->getX() + 1, notis);
  }

  if (this->lifeRemaining == 0) {
    return this->processFinalDeath(notis);
  }

  this->position->respawn(this->map, notis);
  this->lifeRemaining -= 1;
  this->health = config.MAX_HEALTH;

  if (this->ammo < config.BULLET_DROP_WHEN_DIES)
    this->ammo = 0;
  else
    this->ammo -= config.BULLET_DROP_WHEN_DIES;

  return 0;
}

double Player::calculateDistanceTo(Player* p) {
  return sqrt(pow(this->getX() - p->getX(), 2) + pow(this->getY() - p->getY(), 2));
}

bool Player::hasToBeUpdated() {
  return this->hasToBeNotified;
}

int Player::takeDamage(unsigned int damage,
                       WaitingQueue<Notification*>& notis) {
  this->hasToBeNotified = true;

  if (damage >= this->health) {
    return handleDeath(notis);
  }

  this->health -= damage;
  return this->health;
}

void Player::setNotifiable(bool status){
  this->hasToBeNotified = status;
}

int Player::getKills(){
  return this->kills;
}

int Player::getShotsFired(){
  return this->shotsFired;
}

void Player::fillPlayerData(PlayerData& data) {
  this->position->fillData(data);
  data.lives = lifeRemaining;
  data.health = health;
  data.weaponID = this->currentWeapon->getID();
  data.bullets = this->ammo;
  data.score = this->score;
  data.hasKey = this->key;

  return;
}

void Player::moveTo(double x, double y) {
}

void Player::update(float timeElapsed, WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables) {

  if(this->shooting)
    this->shoot(timeElapsed, notis, updatables);

  if(this->position->update(this->map, timeElapsed, notis))
    this->hasToBeNotified = true;
}

void Player::shootRPG(WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables){
  double dirX = this->getDirX();
  double dirY = this->getDirY();
  int uniqueId = map.getAndIncreaseByOneNextUniqueItemId();

  PlayerDropItem* noti = new PlayerDropItem(this->getX() + dirX + this->getPlaneX()/2, this->getY() + dirY + this->getPlaneY()/2, 404, uniqueId);
  notis.push(noti);

  RocketMissile* newMissile = new RocketMissile(this->getX() + dirX, this->getY() + dirY, dirX, dirY, uniqueId, this->getPlaneX()/2, this->getPlaneY()/2);
  updatables.push_back(newMissile);
  return;
}

void Player::shoot(float timeElapsed, WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables){

  Player* receiver = nullptr;

  int att = this->attack(timeElapsed);
  int range = this->getRange();

  if(this->currentWeapon->getID() == 1 || this->currentWeapon->getID() == 2 || this->currentWeapon->getID() == 5){
    this->setShooting(false);
  }

  if(att == -1){
    return;
  }

  if(range == INT_MAX){
    this->shootRPG(notis, updatables);
  }

  if (this->ammo <= 0) {
    this->currentWeapon = this->weapons.at(0);
  }

  ShotsFired* noti = new ShotsFired(this->playerID);
  notis.push(noti);
  int receiverHealth = 0;

  if ((receiver = map.traceAttackFrom(this, range)) != nullptr) {
    att = int((att / sqrt(this->calculateDistanceTo(receiver)))) % 10;
    receiverHealth = receiver->takeDamage(att, notis);

    if((receiverHealth == 0) || (receiverHealth == -1)){
      this->addPoints(config.POINTS_PER_KILL);
      this->kills += 1;
    }
  }
}

double Player::getX() {
  return this->position->getX();
}

double Player::getY() {
  return this->position->getY();
}

double Player::getDirX() {
  return this->position->getDirX();
}

double Player::getDirY() {
  return this->position->getDirY();
}

int Player::attack(float timeElapsed) {

  int ammo = this->ammo;
  int damageDealt = this->currentWeapon->attack(ammo, timeElapsed);
  this->shotsFired += (this->ammo - ammo);
  this->ammo = ammo;

  this->hasToBeNotified = true;
  return damageDealt;
}

int Player::getRange() {
  return this->currentWeapon->getRange();
}

unsigned int Player::ID() {
  return this->playerID;
}

void Player::updateMoveSpeed(double moveSpeed) {
    this->position->updateMoveSpeed(moveSpeed);
}

void Player::updateRotationSpeed(double rotSpeed) {
  this->position->updateRotationSpeed(rotSpeed);
}

void Player::equipWeapon(int weaponPos) {
  if ((weaponPos >= this->weapons.size()) || (this->ammo <= 0)) return;

  this->currentWeapon = this->weapons.at(weaponPos);
  this->hasToBeNotified = true;
}

void Player::pickupKey() {
  this->key = true;
}

bool Player::hasKey() {
  return key;
}

bool Player::hasMaxAmmo() {
  return ammo >= config.MAX_AMMO;
}

void Player::pickUpAmmo() {
  if (this->ammo == 0)
    this->currentWeapon = this->weapons.at(1);

  ammo += config.AMMO_PICK_UP;
  if (ammo > config.MAX_AMMO)
    ammo = config.MAX_AMMO;

  this->hasToBeNotified = true;
}

int Player::getHealth() {
  return this->health;
}

bool Player::hasFullHealth() {
  return this->health == config.MAX_AMMO;
}

void Player::addHealth(int health) {
  this->health += health;

  if (this->health > config.MAX_HEALTH)
    this->health = config.MAX_HEALTH;

  this->hasToBeNotified = true;
}

double Player::getPlaneX(){
  return this->position->getPlaneX();
}

double Player::getPlaneY(){
  return this->position->getPlaneY();
}

void Player::addPoints(int points) {
  this->score += points;
}

int Player::getScore() {
  return this->score;
}

Player::~Player() {
  delete this->position;
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  for (; it != this->weapons.end(); ++it) {
    delete (*it);
  }
}
