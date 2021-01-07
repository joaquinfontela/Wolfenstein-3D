#include "../../../includes/Model/Item/Chest.h"

Chest::Chest(int id, int pointsSumWhenPickedUp) : Item(id) {
  this->pointsSumWhenPickedUp = pointsSumWhenPickedUp;
}

Chest::~Chest() {}

bool Chest::canBePickedUpBy(Player* p) { return true; }

void Chest::pickUp(Player* p) { p->addPoints(this->pointsSumWhenPickedUp); }