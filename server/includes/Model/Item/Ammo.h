#include "Item.h"

class Ammo : public Item {
 public:
  Ammo();
  ~Ammo();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};