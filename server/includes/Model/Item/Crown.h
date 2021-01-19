#ifndef TP_FINAL_CROWN_H
#define TP_FINAL_CROWN_H

#include "Item.h"

class Crown : public Item {
 private:
  int pointsSumWhenPickedUp;

 public:
  Crown(int itemID, int id, int pointsSumWhenPickedUp);
  ~Crown();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};

#endif  // TP_FINAL_CROWN_H
