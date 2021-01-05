#include "../../../includes/Model/Item/Crown.h"

Crown::Crown() : Item() {}

Crown::~Crown() {}

bool Crown::canBePickedUpBy(Player* p) { return true; }

void Crown::pickUp(Player* p) { p->addPoints(200); }