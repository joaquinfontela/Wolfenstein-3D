#include "../../../includes/Model/Item/Food.h"

Food::Food() : Item() {}

Food::~Food() {}

bool Food::canBePickedUpBy(Player& player) { return !player.hasFullHealth(); }

void Food::pickUp(Player& player) { player.addHealth(10); }