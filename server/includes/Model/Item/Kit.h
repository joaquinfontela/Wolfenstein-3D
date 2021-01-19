#ifndef __KIT_H__
#define __KIT_H__

#include "Item.h"

class Kit : public Item {
 private:
  int healthSumWhenPickedUp;

 public:
  Kit(int itemID, int id, int healthSumWhenPickedUp);

  bool canBePickedUpBy(Player* p);
  void pickUp(Player* p);
};

#endif
