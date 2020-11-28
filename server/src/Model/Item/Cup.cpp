#include "../../../includes/Model/Item/Cup.h"

Cup::Cup() : Item() {}

Cup::~Cup() {}

bool Cup::canBePickedUpBy(Player& player) { return true; }

void Cup::pickUp(Player& player) { player.addPoints(50); }