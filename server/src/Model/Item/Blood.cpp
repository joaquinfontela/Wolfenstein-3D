#include "../../../includes/Model/Item/Blood.h"
#include <iostream>

Blood::Blood(int itemID, int id, int healthSumWhenPickedUp, int maxHealthToPickUp)
    : Item(itemID, id) {
  this->healthSumWhenPickedUp = healthSumWhenPickedUp;
  this->maxHealthToPickUp = maxHealthToPickUp;
}

bool Blood::canBePickedUpBy(Player* p) {

  return (p->getHealth() <= this->maxHealthToPickUp);
}

void Blood::pickUp(Player* p) { p->addHealth(this->healthSumWhenPickedUp); }
