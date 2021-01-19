#include "../../../includes/Model/Item/Cup.h"

Cup::Cup(int itemID, int id, int pointsSumWhenPickedUp) : Item(itemID, id) {
  this->pointsSumWhenPickedUp = pointsSumWhenPickedUp;
}

Cup::~Cup() {}

bool Cup::canBePickedUpBy(Player* p) { return true; }

void Cup::pickUp(Player* p) { p->addPoints(this->pointsSumWhenPickedUp); }
