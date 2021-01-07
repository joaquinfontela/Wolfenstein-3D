#include "../../../includes/Model/Item/Blood.h"

Blood::Blood(int id, int healthSumWhenPickedUp, int maxHealthToPickUp)
    : Item(id) {
  this->healthSumWhenPickedUp = healthSumWhenPickedUp;
  this->maxHealthToPickUp = maxHealthToPickUp;
}

bool Blood::canBePickedUpBy(Player* p) {
  return (p->getHealth() <= this->maxHealthToPickUp);
}

void Blood::pickUp(Player* p) { p->addHealth(this->healthSumWhenPickedUp); }
