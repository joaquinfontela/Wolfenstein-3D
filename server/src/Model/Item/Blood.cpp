#include "../../../includes/Model/Item/Blood.h"

Blood::Blood() : Item() {}

Blood::~Blood() {}

void Blood::pickUp(Player& player) { player.addHealth(1); }
