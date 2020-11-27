#include "Item.h"

class MedKit : public Item {
 public:
  void pickUp(Player player) override;
};