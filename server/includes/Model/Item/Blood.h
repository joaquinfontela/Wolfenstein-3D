#include "Item.h"

class Blood : public Item {
 public:
  Blood();
  ~Blood();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};