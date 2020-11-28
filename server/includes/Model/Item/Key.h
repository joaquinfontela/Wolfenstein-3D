#include "Item.h"

class Key : public Item {
 public:
  Key();
  ~Key();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};