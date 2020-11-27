#include "StockableItem.h"

class Key : public StockableItem {
 public:
  void stockItem(Player player) override;
};