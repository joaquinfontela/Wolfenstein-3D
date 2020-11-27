#ifndef TP_FINAL_CHEST_H
#define TP_FINAL_CHEST_H

#include "Item.h"

class Chest : public Item {
 public:
  void pickUp(Player player) override;
};

#endif  // TP_FINAL_CHEST_H
