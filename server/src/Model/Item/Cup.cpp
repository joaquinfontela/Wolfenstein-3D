#include "../../../includes/Model/Item/Cup.h"

Cup::Cup() : Item() {}

Cup::~Cup() {}

bool Cup::canBePickedUpBy(Player* p) { return true; }

void Cup::pickUp(Player* p) { p->addPoints(50); }