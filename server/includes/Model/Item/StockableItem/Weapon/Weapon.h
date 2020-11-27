#include "../StockableItem.h"

class Weapon : public StockableItem {
 public:
  virtual void attack() = 0;
  void stockItem(Player player) override;
};