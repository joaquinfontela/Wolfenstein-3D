#include "Item.h"

class Cross : public Item {
 public:
  Cross(int id);
  ~Cross();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};