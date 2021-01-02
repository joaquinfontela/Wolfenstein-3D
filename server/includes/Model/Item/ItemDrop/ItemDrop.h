#ifndef TP_FINAL_ITEMDROP_H
#define TP_FINAL_ITEMDROP_H

#include "../../Player/Player.h"
#include "../Item.h"
#include "./ItemFactory.h"

class ItemDrop {
 protected:
  Item* item;
  bool canBePickedUpBy(Player& player);
  void pickUp(Player& player);

 public:
  ItemDrop(int itemId);
  bool pickUpIfPossible(Player& player);
  int id;
  //~ItemDrop();
};

#endif  // TP_FINAL_ITEMDROP_H
