#ifndef ITEM_H
#define ITEM_H

#include "../Player/Player.h"

class Item {
 public:
  virtual ~Item() = 0;
  virtual void pickUp(Player& player) = 0;
  virtual bool canBePickedUpBy(Player& player) = 0;
};

#endif