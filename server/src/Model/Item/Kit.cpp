#include "../../../includes/Model/Item/Kit.h"

Kit::Kit(int id, int healthSumWhenPickedUp) : Item(id) {
  this->healthSumWhenPickedUp = healthSumWhenPickedUp;
}

bool Kit::canBePickedUpBy(Player* p) { return !p->hasFullHealth(); }

void Kit::pickUp(Player* p) {
  // Probablemente la vida deberia venir del configFile por lo que capaz deberia
  // recibir la vida que quiero que sume por parametro del constructor.
  p->addHealth(this->healthSumWhenPickedUp);
}
