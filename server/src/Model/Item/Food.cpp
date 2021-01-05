#include "../../../includes/Model/Item/Food.h"

Food::Food(int id) : Item(id) {}

Food::~Food() {}

bool Food::canBePickedUpBy(Player* p) { return !p->hasFullHealth(); }

void Food::pickUp(Player* p) { p->addHealth(10); }