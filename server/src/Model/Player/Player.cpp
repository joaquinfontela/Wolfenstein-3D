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
#include "../../../includes/Control/UpdatableEvent/RocketMissile.h"



Player::Player(YAMLConfigReader yamlConfigReader, Map& map,
               unsigned int playerID)
    : health(yamlConfigReader.getMaxHealth()),
      MAX_HEALTH(yamlConfigReader.getMaxHealth()),
      lifeRemaining(yamlConfigReader.getMaxReviveTimes()),
      ammo(yamlConfigReader.getBulletAmountAtStart()),
      MAX_AMMO(yamlConfigReader.getMaxAmountOfBullets()),
      BULLET_DROP_WHEN_DIES(
          yamlConfigReader.getBulletAmountDropWhenPlayerDies()),
      AMMO_PICK_UP(yamlConfigReader.getBulletAmountWhenPickUpAmmo()),
      POINTS_PER_KILL(yamlConfigReader.getPointsPerKill()),
      key(false),
      score(0),
      dirX(-1),
      dirY(0),
      rotSpeed(0.0),
      moveSpeed(0.0),
      hasToBeNotified(false),
      map(map) {

  this->playerID = playerID;
  this->planeY = 0.66;
  this->planeX = 0;
  this->shooting = false;
  this->isAdmin = false;

  std::tie(this->x, this->y) = map.handleRespawn();
  map.addPlayer(this->x, this->y, this);
  weapons.push_back(
      weaponFactory.getWeapon(1, Map::getAndIncreaseByOneNextUniqueItemId()));
  weapons.push_back(
      weaponFactory.getWeapon(2, Map::getAndIncreaseByOneNextUniqueItemId()));
  this->currentWeapon = weapons.at(1);
}

Player::Player(YAMLConfigReader yamlConfigReader)
    : health(yamlConfigReader.getMaxHealth()),
      MAX_HEALTH(yamlConfigReader.getMaxHealth()),
      lifeRemaining(yamlConfigReader.getMaxReviveTimes()),
      ammo(yamlConfigReader.getBulletAmountAtStart()),
      MAX_AMMO(yamlConfigReader.getMaxAmountOfBullets()),
      BULLET_DROP_WHEN_DIES(
          yamlConfigReader.getBulletAmountDropWhenPlayerDies()),
      AMMO_PICK_UP(yamlConfigReader.getBulletAmountWhenPickUpAmmo()),
      POINTS_PER_KILL(yamlConfigReader.getPointsPerKill()),
      key(false),
      score(0),
      x(6.0),
      y(4.0),
      dirX(-1),
      dirY(0),
      rotSpeed(0.0),
      moveSpeed(0.0),
      hasToBeNotified(false),
      map(map) {
  weapons.push_back(
      weaponFactory.getWeapon(1, Map::getAndIncreaseByOneNextUniqueItemId()));
  weapons.push_back(
      weaponFactory.getWeapon(2, Map::getAndIncreaseByOneNextUniqueItemId()));
  this->currentWeapon = weapons.at(1);
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

void Player::addWeapon(Weapon* weapon) { this->weapons.push_back(weapon); }

bool Player::collidesWith(double x, double y) {
  return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2)) <= 0.25;
}

void Player::respawn(WaitingQueue<Notification*>& notis) {
  double x, y;

  std::tie(x, y) = map.handleRespawn();
  map.moveTo(this->x, this->y, x, y, this, notis);

  this->x = x;
  this->y = y;
}

int Player::handleDeath(WaitingQueue<Notification*>& notis) {
  if (this->lifeRemaining == 0) {
    this->health = 0;
    return -1;
  }

  PlayerDied* noti = new PlayerDied(this->playerID);
  notis.push(noti);

  map.addAmmoDropAt(this->y + 1, this->x + 1, notis);
  this->respawn(notis);
  if (this->key) {
    this->key = false;
    map.addKeyDropAt(this->y + 1, this->x + 1, notis);
  }

  this->lifeRemaining -= 1;
  this->health = this->MAX_HEALTH;  // Deberia restaurar la vida al maximo.

  if (this->ammo < this->BULLET_DROP_WHEN_DIES)
    this->ammo = 0;
  else
    this->ammo -= this->BULLET_DROP_WHEN_DIES;

  return 0;  // Devuelvo valor indicando que mi vida quedo en 0.
}

double Player::calculateDistanceTo(Player* p) {
  return sqrt(pow(this->x - p->getX(), 2) + pow(this->y - p->getY(), 2));
}

bool Player::hasToBeUpdated() { return this->hasToBeNotified; }

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

void Player::fillPlayerData(PlayerData& data) {
  data.posX = this->x;
  data.posY = this->y;
  data.dirX = this->dirX;
  data.dirY = this->dirY;
  data.rotSpeed = this->rotSpeed;
  data.lives = lifeRemaining;
  data.health = health;
  data.weaponID = this->currentWeapon->getID();
  data.bullets = this->ammo;
  data.score = score;


  return;
}

void Player::moveTo(double x, double y) {
  this->x = x;
  this->y = y;
}

void Player::update(float timeElapsed, WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables) {

  if(this->shooting)
  this->shoot(timeElapsed, notis, updatables);

  if (moveSpeed == 0.0 && rotSpeed == 0.0) return;


  double newX = x + dirX * (moveSpeed * (timeElapsed));
  double newY = y + dirY * (moveSpeed * (timeElapsed));

  if (map.moveTo(x, y, newX, newY, this, notis)) {
    x = newX;
    y = newY;
  }

  double oldDirX = dirX;

  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

  double oldPlaneX = this->planeX;
  this->planeX = ((this->planeX) * cos(rotSpeed)) - (this->planeY * sin(rotSpeed));
  this->planeY = (oldPlaneX * sin(rotSpeed)) + (this->planeY * cos(rotSpeed));


  this->hasToBeNotified = true;
}

void Player::shootRPG(WaitingQueue<Notification*>& notis, std::list<Updatable*>& updatables){
  double dirX = this->getDirX();
  double dirY = this->getDirY();
  int uniqueId = Map::getAndIncreaseByOneNextUniqueItemId();
  PlayerDropItem* noti = new PlayerDropItem(this->getX() + dirX + this->planeX/2, this->getY() + dirY + this->planeY/2, 404, uniqueId);
  notis.push(noti);
  RocketMissile* newMissile = new RocketMissile(this->getX() + dirX + this->planeX/2, this->getY() + dirY + this->planeY/2, dirX, dirY, uniqueId);
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

  if(range == INT_MAX){ // Por el momento, INT_MAX siginifica que lanzo un RPG. Cambiar a un metodo del estilo hasRPG();
    this->shootRPG(notis, updatables);
  }

  ShotsFired* noti = new ShotsFired(this->playerID);
  notis.push(noti);
  int receiverHealth = 0;

  if ((receiver = map.traceAttackFrom(this, range)) != nullptr) {
    att = int((att / sqrt(this->calculateDistanceTo(receiver)))) % 10;
    receiverHealth = receiver->takeDamage(att, notis);

    if((receiverHealth == 0) || (receiverHealth == -1))
      this->addPoints(POINTS_PER_KILL);
  }
}

double Player::getX() { return this->x; }

double Player::getY() { return this->y; }

double Player::getDirX() { return this->dirX; }

double Player::getDirY() { return this->dirY; }

int Player::attack(float timeElapsed) {
  // Deberia pedirle a su arma que ataque, devolviendo el daño que hizo.
  // Luego le pregunto al arma cuantas balas tiene, si no tiene mas disponible,
  // cambio a cuchillo. Setearia Notificable a true salvo que tenga cuchillo.

  int ammo = this->ammo;
  int damageDealt = this->currentWeapon->attack(ammo, timeElapsed);
  this->ammo = ammo;

  if (this->ammo <= 0) {
    this->currentWeapon = this->weapons.at(0);
  }

  this->hasToBeNotified = true;
  return damageDealt;
}

int Player::getRange() { return this->currentWeapon->getRange(); }

unsigned int Player::ID() { return this->playerID; }

void Player::updateMoveSpeed(double moveSpeed) {
   this->moveSpeed += moveSpeed;

   if(this->moveSpeed < -6.5)
     this->moveSpeed = -6.5;
   else if(this->moveSpeed > 6.5)
     this->moveSpeed = 6.5;
  }

void Player::updateRotationSpeed(double rotSpeed) {
  this->rotSpeed += rotSpeed;

  if(this->rotSpeed < -0.125)
    this->rotSpeed = -0.125;
  else if(this->rotSpeed > 0.125)
    this->rotSpeed = 0.125;

}

void Player::equipWeapon(int weaponPos) {
  if ((weaponPos >= this->weapons.size()) || (this->ammo <= 0)) return;

  this->currentWeapon = this->weapons.at(weaponPos);
  this->hasToBeNotified = true;
}

void Player::pickupKey() { this->key = true; }

bool Player::hasKey() { return key; }

bool Player::hasMaxAmmo() { return ammo >= this->MAX_AMMO; }

void Player::pickUpAmmo() {
  if (this->ammo == 0) this->currentWeapon = this->weapons.at(1);

  ammo += this->AMMO_PICK_UP;
  if (ammo > this->MAX_AMMO) ammo = this->MAX_AMMO;
  this->hasToBeNotified = true;
}

int Player::getHealth() { return this->health; }

bool Player::hasFullHealth() { return this->health == this->MAX_HEALTH; }

void Player::addHealth(int health) {
  this->health += health;
  if (this->health > MAX_HEALTH) this->health = this->MAX_HEALTH;
  this->hasToBeNotified = true;
}

void Player::addPoints(int points) { this->score += points; }

int Player::getScore() { return this->score; }

Player::~Player() {
  std::vector<Weapon*>::iterator it = this->weapons.begin();

  for (; it != this->weapons.end(); ++it) {
    delete (*it);
  }
}
