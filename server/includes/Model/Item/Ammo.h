#include "Item.h"

class Ammo : public Item {
 public:
  void pickUp(Player player) override;
};