#include "../../../includes/Model/Item/Blood.h"

void Blood::pickUp(Player& player) { player.addHealth(1); }
