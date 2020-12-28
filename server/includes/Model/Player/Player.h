#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Item/Item.h"

typedef struct PlayerData{

  double posX, posY;
  double dirX, dirY;
  // int weaponID;
  double rotSpeed;
  // int health;
  // int lives;
  //
}PlayerData;

class Item;

class Player {
 private:
  double x, y;
  double dirX, dirY;
  double rotSpeed;
  double moveSpeed;

  bool hasToBeNotified;

  int score;
  unsigned int health, lifeRemaining, ammo;
  Item* weapon;
  bool key;

  int handleDeath();

 public:
  Player(unsigned int hp, unsigned int lifes);
  Player() {}
  int takeDamage(unsigned int damage);

  // Devuelve cuanto daño hace un ataque con su arma.
  // Si se queda sin balas, cambia de arma.
  int attack();
  void updateMoveSpeed(double movSpeed);
  void updateRotationSpeed(double rotSpeed);
  void equipWeapon(Item* weapon);

  bool hasToBeUpdated();
  void update();


  void pickupKey();
  bool hasKey();

  bool hasMaxAmmo();
  void pickUpAmmo();

  int getHealth();
  bool hasFullHealth();
  void addHealth(int health);

  void addPoints(int points);
  int getScore();
};

#endif
