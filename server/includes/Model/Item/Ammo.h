#include "Item.h"

class Ammo : public Item {
 public:
  Ammo(int itemID, int id);
  ~Ammo();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};
