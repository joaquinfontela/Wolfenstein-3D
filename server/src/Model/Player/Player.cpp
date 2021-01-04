#include "../../../includes/Model/Player/Player.h"

#include "../../../includes/Model/Item/Weapon.h"
#include <math.h>
#include <iostream>
#include <tuple>
#include <functional>

#define MAX_AMMO 1000
#define MAX_HEALTH 100

Player::Player(unsigned int hp, unsigned int lifes, Map& map, unsigned int playerID)
    : health(hp), lifeRemaining(lifes), ammo(0), key(false), score(0), x(6.0), y(4.0), dirX(-1), dirY(0), rotSpeed(0.0), moveSpeed(0.0), hasToBeNotified(false)  {

      this->playerID = playerID;
      map.addPlayer(6, 4, this);

    }

Player::Player(unsigned int hp, unsigned int lifes)
        : health(hp), lifeRemaining(lifes), ammo(0), key(false), score(0), x(6.0), y(4.0), dirX(-1), dirY(0), rotSpeed(0.0), moveSpeed(0.0), hasToBeNotified(false)  {}


bool Player::collidesWith(double x, double y){

  return fabs(this->x - x) < 5 && fabs(this->y - y) < 5;
}
int Player::handleDeath(Map& map) {
  if (this->lifeRemaining == 0) {
    this->health = 0;
    return -1;  // El jugador ya no puede respawnear.
  }


  this->lifeRemaining -= 1;
  this->health = MAX_HEALTH;  // Deberia restaurar la vida al maximo.
  this->ammo -= 10;
  this->key = false;

  double x, y;
  std::tie(x, y) = map.handleRespawn();
  map.moveTo(this->x, this->y, x, y, this);
  this->x = x;
  this->y = y;

  return 0;  // Devuelvo valor indicando que mi vida quedo en 0.
}

bool Player::hasToBeUpdated(){
  return this->hasToBeNotified;
}

int Player::takeDamage(unsigned int damage, Map& map) {


  std::cout<<"[GAME LOGIC] Player has received: "<<damage<< " damage."<<std::endl;
  this->hasToBeNotified = true;

  if (damage >= this->health) {
    return handleDeath(map);
  }

  this->health -= damage;
  return this->health;
}

void Player::fillPlayerData(PlayerData& data){

  data.posX = this->x;
  data.posY = this->y;
  data.dirX = this->dirX;
  data.dirY = this->dirY;
  data.rotSpeed = this->rotSpeed;
  data.lives = lifeRemaining;
  data.health = health;

  this->hasToBeNotified = false;
  return;
}

void Player::update(Map& map){

  if(moveSpeed == 0.0 && rotSpeed == 0.0)
    return;


  double newX =  x + dirX * moveSpeed;
  double newY = y + dirY * moveSpeed;

  if(map.moveTo(x, y, newX, newY, this)){
    x = newX;
    y = newY;
  }


  double oldDirX = dirX;

  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);


  this->hasToBeNotified = true;
}

double Player::getX(){
  return this->x;
}

double Player::getY(){
  return this->y;
}

double Player::getDirX(){
  return this->dirX;
}

double Player::getDirY(){
  return this->dirY;
}

int Player::attack() {
  // Deberia pedirle a su arma que ataque, devolviendo el daño que hizo.
  // Luego le pregunto al arma cuantas balas tiene, si no tiene mas disponible,
  // cambio a cuchillo. Setearia Notificable a true salvo que tenga cuchillo.
  return 10;
}

unsigned int Player::ID(){
  return this->playerID;
}

void Player::updateMoveSpeed(double moveSpeed){
  this->moveSpeed += moveSpeed;
}

void Player::updateRotationSpeed(double rotSpeed){
  this->rotSpeed += rotSpeed;
}

void Player::equipWeapon(Weapon* weapon) {
   this->weapon = (Weapon*)weapon;

   this->hasToBeNotified = true;

  }

void Player::pickupKey() { this->key = true; }

bool Player::hasKey() { return key; }

bool Player::hasMaxAmmo() { return ammo < MAX_AMMO; }

void Player::pickUpAmmo() {
  ammo += 5;
  if (ammo > MAX_AMMO) ammo = MAX_AMMO;

  this->hasToBeNotified = true;
}

int Player::getHealth() { return this->health; }

bool Player::hasFullHealth() { return this->health == MAX_HEALTH; }

void Player::addHealth(int health) {
  this->health += health;
  if (this->health > MAX_HEALTH) this->health = MAX_HEALTH;

  this->hasToBeNotified = true;
}

void Player::addPoints(int points) { this->score += points; }

int Player::getScore() { return this->score; }


Player::~Player(){
  //delete this->weapon;
}
