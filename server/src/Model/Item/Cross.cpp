#include "../../../includes/Model/Item/Cross.h"

Cross::Cross(int id, int pointsSumWhenPickedUp) : Item(id) {
  this->pointsSumWhenPickedUp = pointsSumWhenPickedUp;
}

Cross::~Cross() {}

bool Cross::canBePickedUpBy(Player* p) { return true; }

void Cross::pickUp(Player* p) { p->addPoints(this->pointsSumWhenPickedUp); }