#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Item/Weapon/Weapon.h"

class Player {
 private:
  int x, y;
  int score;
  unsigned int health, lifeRemaining;
  // Weapon* weapon;
  bool key;

  int handleDeath();

 public:
  Player(unsigned int hp, unsigned int lifes);
  Player() {}
  int takeDamage(unsigned int damage);

  // Devuelve cuanto daño hace un ataque con su arma.
  // Si se queda sin balas, cambia de arma.
  int attack();

  void equipWeapon(Weapon* weapon);

  void pickupKey();
  bool hasKey();

  void pickUpAmmo();

  int getHealth();
  bool hasFullHealth();
  void addHealth(int health);

  void addPoints(int points);
  int getScore();
};

#endif