#include "../../../includes/Model/Item/Cross.h"

Cross::Cross() : Item() {}

Cross::~Cross() {}

bool Cross::canBePickedUpBy(Player& player) { return true; }

void Cross::pickUp(Player& player) { player.addPoints(10); }