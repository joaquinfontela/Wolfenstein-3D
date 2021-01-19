#include "Item.h"

class Cross : public Item {
 private:
  int pointsSumWhenPickedUp;

 public:
  Cross(int itemID, int id, int pointsSumWhenPickedUp);
  ~Cross();
  void pickUp(Player* p) override;
  bool canBePickedUpBy(Player* p) override;
};
