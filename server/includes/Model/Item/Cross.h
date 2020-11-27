#include "Item.h"

class Cross : public Item {
 public:
  void pickUp(Player& player) override;
};