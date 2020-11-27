#ifndef ITEM_H
#define ITEM_H

class Player;
#include "../Player/Player.h"

class Item {
 public:
  virtual void pickUp(Player player) = 0;
};

#endif