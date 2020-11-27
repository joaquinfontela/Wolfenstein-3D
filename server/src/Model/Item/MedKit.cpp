#include "../../../includes/Model/Item/MedKit.h"

void MedKit::pickUp(Player& player) { player.addHealth(20); }