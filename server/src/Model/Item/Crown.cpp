#include "../../../includes/Model/Item/Crown.h"

Crown::Crown() : Item() {}

Crown::~Crown() {}

bool Crown::canBePickedUpBy(Player& player) { return true; }

void Crown::pickUp(Player& player) { player.addPoints(200); }
