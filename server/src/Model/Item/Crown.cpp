#include "../../../includes/Model/Item/Crown.h"

Crown::Crown() : Item() {}

Crown::~Crown() {}

void Crown::pickUp(Player& player) { player.addPoints(200); }
