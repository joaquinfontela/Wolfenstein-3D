#include "Item.h"

class Food : public Item {
 public:
  Food();
  ~Food();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};