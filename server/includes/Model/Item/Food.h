#include "Item.h"

class Food : public Item {
 public:
  Food(int id);
  ~Food();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};