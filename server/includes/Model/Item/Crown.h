#ifndef TP_FINAL_CROWN_H
#define TP_FINAL_CROWN_H

#include "Item.h"

class Crown : public Item {
 public:
  Crown();
  ~Crown();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};

#endif  // TP_FINAL_CROWN_H
