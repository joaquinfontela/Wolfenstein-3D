#include "../../../includes/Model/Item/Chest.h"

Chest::Chest() : Item() {}

Chest::~Chest() {}

bool Chest::canBePickedUpBy(Player& player) { return true; }

void Chest::pickUp(Player& player) { player.addPoints(100); }
