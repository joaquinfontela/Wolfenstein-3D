#include "../../../includes/Model/Item/Kit.h"

Kit::Kit(int itemID, int id, int healthSumWhenPickedUp) : Item(itemID, id) {
  this->healthSumWhenPickedUp = healthSumWhenPickedUp;
}

bool Kit::canBePickedUpBy(Player* p) { return !p->hasFullHealth(); }

void Kit::pickUp(Player* p) { p->addHealth(this->healthSumWhenPickedUp); }
