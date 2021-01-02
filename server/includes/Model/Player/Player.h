#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Item/Item.h"
#include "../../../../common/includes/PlayerData.h"
#include "../Item/Weapon/Weapon.h"
#include "../Map/Map.h"


class Map;
class Weapon;


class Player {
 private:
  double x, y;
  double dirX, dirY;
  double rotSpeed;
  double moveSpeed;
  unsigned int playerID;

  bool hasToBeNotified;

  int score;
  unsigned int health, lifeRemaining, ammo;
  Weapon* weapon;
  bool key;

  int handleDeath();

 public:
  Player(unsigned int hp, unsigned int lifes, Map& map, unsigned int playerID);
  Player(unsigned int hp, unsigned int lifes);
  Player() {}
  int takeDamage(unsigned int damage);

  unsigned int ID();

  double getX();
  double getY();
  double getDirX();
  double getDirY();

  void fillPlayerData(PlayerData& data);

  // Devuelve cuanto daño hace un ataque con su arma.
  // Si se queda sin balas, cambia de arma.
  int attack();
  void updateMoveSpeed(double movSpeed);
  void updateRotationSpeed(double rotSpeed);
  void equipWeapon(Weapon* weapon);


  bool collidesWith(double x, double y);

  bool hasToBeUpdated();
  void update(Map& map);


  void pickupKey();
  bool hasKey();

  bool hasMaxAmmo();
  void pickUpAmmo();

  int getHealth();
  bool hasFullHealth();
  void addHealth(int health);

  void addPoints(int points);
  int getScore();

  ~Player();
};

#endif
