#include "../../../includes/Model/Item/Cup.h"

Cup::Cup() : Item() {}

Cup::~Cup() {}

void Cup::pickUp(Player& player) { player.addPoints(50); }