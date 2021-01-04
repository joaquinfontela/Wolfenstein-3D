#ifndef TP_FINAL_CUP_H
#define TP_FINAL_CUP_H

#include "Item.h"

class Cup : public Item {
 public:
  Cup();
  ~Cup();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};

#endif  // TP_FINAL_CUP_H