#include "../../../includes/Model/Item/Cross.h"

Cross::Cross(int id) : Item(id) {}

Cross::~Cross() {}

bool Cross::canBePickedUpBy(Player* p) { return true; }

void Cross::pickUp(Player* p) { p->addPoints(10); }