#ifndef STOCKABLE_ITEM_H
#define STOCKABLE_ITEM_H

#include "../Item.h"

class StockableItem : public Item {
 public:
  virtual void stockItem(Player player) = 0;
};

#endif