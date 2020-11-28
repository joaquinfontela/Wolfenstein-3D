#include "Item.h"

class Cross : public Item {
 public:
  Cross();
  ~Cross();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};