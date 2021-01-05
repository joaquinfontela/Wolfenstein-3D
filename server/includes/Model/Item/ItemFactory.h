#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "Item.h"

class ItemFactory {
 public:
  Item* getItem(int itemTypeId, int uniqueId);
};

#endif