#ifndef __ITEM_FACTORY_H__
#define __ITEM_FACTORY_H__


#include "../Item.h"

class Item;

class ItemFactory {
 public:
  Item* getItem(int itemId);
};


#endif
