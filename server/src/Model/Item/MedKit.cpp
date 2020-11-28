#include "../../../includes/Model/Item/MedKit.h"

MedKit::MedKit() : Item() {}

MedKit::~MedKit() {}

bool MedKit::canBePickedUpBy(Player& player) { return !player.hasFullHealth(); }

void MedKit::pickUp(Player& player) { player.addHealth(20); }