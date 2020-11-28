#include "../../../includes/Model/Item/Blood.h"

Blood::Blood() : Item() {}

Blood::~Blood() {}

bool Blood::canBePickedUpBy(Player& player) { return player.getHealth() < 11; }

void Blood::pickUp(Player& player) { player.addHealth(1); }
