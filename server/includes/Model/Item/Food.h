#include "Item.h"

class Food : public Item {
 private:
  int healthSumWhenPickedUp;

 public:
  Food(int itemID, int id, int healthSumWhenPickedUp);
  ~Food();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};
