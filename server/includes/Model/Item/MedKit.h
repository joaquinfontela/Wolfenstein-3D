#include "Item.h"

class MedKit : public Item {
 public:
  MedKit();
  ~MedKit();
  void pickUp(Player& player) override;
  bool canBePickedUpBy(Player& player);
};