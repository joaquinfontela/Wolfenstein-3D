#ifndef TP_FINAL_ITEMDROP_H
#define TP_FINAL_ITEMDROP_H

#include "../../Player/Player.h"
#include "../Item.h"

class ItemDrop {
 protected:
  Item* item;
  bool canBePickedUpBy(Player& player);
  void pickUp(Player& player);

 public:
  ItemDrop(int itemId);
  bool pickUpIfPossible(Player& player);
  int itemId;
};

#endif  // TP_FINAL_ITEMDROP_H
