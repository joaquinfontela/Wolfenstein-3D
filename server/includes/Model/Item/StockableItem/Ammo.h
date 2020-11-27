#include "StockableItem.h"

class Ammo : public StockableItem {
 public:
  void stockItem(Player player) override;
};