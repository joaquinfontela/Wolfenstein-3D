#ifndef TP_FINAL_ITEMDROP_H
#define TP_FINAL_ITEMDROP_H

#include "../Item.h"
class Item;

class ItemDrop {
 protected:
  Item& item;
  bool canBePickedUpBy(Player& player);
  void pickUp(Player& player);

 public:
  ItemDrop(Item& anITem);
  bool pickUpIfPossible(Player& player);
};

#endif  // TP_FINAL_ITEMDROP_H
