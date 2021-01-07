#include "../../../includes/Model/Item/Crown.h"

Crown::Crown(int id, int pointsSumWhenPickedUp) : Item(id) {
  this->pointsSumWhenPickedUp = pointsSumWhenPickedUp;
}

Crown::~Crown() {}

bool Crown::canBePickedUpBy(Player* p) { return true; }

void Crown::pickUp(Player* p) { p->addPoints(this->pointsSumWhenPickedUp); }