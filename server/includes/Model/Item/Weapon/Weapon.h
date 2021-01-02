#ifndef WEAPON_H
#define WEAPON_H



#include "../../Player/Player.h"


class Player;

class Weapon{
 public:
  virtual ~Weapon() = 0;
  virtual unsigned int attack() = 0;
  void pickUp(Player& player);
  bool canBePickedUpBy(Player& player);
};

#endif
