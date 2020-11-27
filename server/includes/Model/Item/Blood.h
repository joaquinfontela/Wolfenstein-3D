#include "Item.h"

class Blood : public Item {
 public:
  void pickUp(Player& player) override;
};