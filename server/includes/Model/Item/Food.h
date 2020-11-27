#include "Item.h"

class Food : public Item {
 public:
  void pickUp(Player& player) override;
};