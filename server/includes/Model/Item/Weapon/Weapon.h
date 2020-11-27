#ifndef WEAPON_H
#define WEAPON_H

#include "../Item.h"

class Weapon : public Item {
 public:
  virtual void attack() = 0;
  void pickUp(Player& player) override;
};

#endif