#include "../../../includes/Model/Item/Food.h"

Food::Food(int id, int healthSumWhenPickedUp) : Item(id) {
  this->healthSumWhenPickedUp = healthSumWhenPickedUp;
}

Food::~Food() {}

bool Food::canBePickedUpBy(Player* p) { return !p->hasFullHealth(); }

void Food::pickUp(Player* p) { p->addHealth(this->healthSumWhenPickedUp); }