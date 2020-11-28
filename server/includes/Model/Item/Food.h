#include "Item.h"

class Food : public Item {
 public:
  Food();
  ~Food();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};