#ifndef TP_FINAL_CHEST_H
#define TP_FINAL_CHEST_H

#include "Item.h"

class Chest : public Item {
 private:
  int pointsSumWhenPickedUp;

 public:
  Chest(int itemID, int id, int pointsSumWhenPickedUp);
  ~Chest();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};

#endif  // TP_FINAL_CHEST_H
