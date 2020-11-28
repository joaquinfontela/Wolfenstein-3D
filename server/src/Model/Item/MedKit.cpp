#include "../../../includes/Model/Item/MedKit.h"

MedKit::MedKit() : Item() {}

MedKit::~MedKit() {}

void MedKit::pickUp(Player& player) { player.addHealth(20); }