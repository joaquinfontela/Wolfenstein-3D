#include "Item.h"

class Key : public Item {
 public:
  void pickUp(Player player) override;
};