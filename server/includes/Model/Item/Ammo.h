#include "Item.h"

class Ammo : public Item {
 public:
  Ammo();
  ~Ammo();
  void pickUp(Player& player) override;
};