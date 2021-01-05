#include "../../../includes/Model/Item/Chest.h"

Chest::Chest(int id) : Item(id) {}

Chest::~Chest() {}

bool Chest::canBePickedUpBy(Player* p) { return true; }

void Chest::pickUp(Player* p) { p->addPoints(100); }