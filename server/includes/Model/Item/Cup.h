#ifndef TP_FINAL_CUP_H
#define TP_FINAL_CUP_H

#include "Item.h"

class Cup : public Item {
 private:
  int pointsSumWhenPickedUp;

 public:
  Cup(int itemID, int id, int pointsSumWhenPickedUp);
  ~Cup();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};

#endif  // TP_FINAL_CUP_H
