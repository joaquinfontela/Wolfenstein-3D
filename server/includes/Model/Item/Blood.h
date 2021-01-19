#ifndef __BLOOD_H__
#define __BLOOD_H__

#include "Item.h"

class Blood : public Item {
 private:
  int healthSumWhenPickedUp;
  int maxHealthToPickUp;

 public:
  Blood(int itemID, int id, int healthSumWhenPickedUp, int maxHealthToPickUp);
  bool canBePickedUpBy(Player* p);
  void pickUp(Player* p);
};

#endif
