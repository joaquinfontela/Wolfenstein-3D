#include "../../../includes/Model/Item/Cross.h"

Cross::Cross() : Item() {}

Cross::~Cross() {}

void Cross::pickUp(Player& player) { player.addPoints(10); }