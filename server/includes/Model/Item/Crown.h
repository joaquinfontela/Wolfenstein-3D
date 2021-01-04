#ifndef TP_FINAL_CROWN_H
#define TP_FINAL_CROWN_H

#include "Item.h"

class Crown : public Item {
 public:
  Crown();
  ~Crown();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};

#endif  // TP_FINAL_CROWN_H