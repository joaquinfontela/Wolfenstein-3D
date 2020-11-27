#include "../../../../includes/Model/Item/ItemDrop/ItemDrop.h"

ItemDrop::ItemDrop(Item &anItem) : item(anItem) {}

bool ItemDrop::canBePickedUpBy(Player &player) {
  // return item.canBePickedUpBy(player);
  return true;
}

void ItemDrop::pickUp(Player &player) { item.pickUp(player); }

bool ItemDrop::pickUpIfPossible(Player &player) {
  bool wasPickedUp;
  if ((wasPickedUp = canBePickedUpBy(player))) pickUp(player);
  return wasPickedUp;
}
