#include "../../../includes/Model/Item/Chest.h"

Chest::Chest() : Item() {}

Chest::~Chest() {}

void Chest::pickUp(Player& player) { player.addPoints(100); }
