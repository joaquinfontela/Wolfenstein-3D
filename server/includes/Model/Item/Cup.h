#ifndef TP_FINAL_CUP_H
#define TP_FINAL_CUP_H

#include "Item.h"

class Cup : public Item {
 public:
  Cup();
  ~Cup();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};

#endif  // TP_FINAL_CUP_H
