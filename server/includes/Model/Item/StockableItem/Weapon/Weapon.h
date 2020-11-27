#ifndef WEAPON_H
#define WEAPON_H

#include "../StockableItem.h"

class Weapon : public StockableItem {
 public:
  virtual void attack() = 0;
  void stockItem(Player player) override;
};

#endif