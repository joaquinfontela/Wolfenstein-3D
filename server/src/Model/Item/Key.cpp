#include "../../../includes/Model/Item/Key.h"

Key::Key() : Item() {}

Key::~Key() {}

bool Key::canBePickedUpBy(Player& player) { return !player.hasKey(); }

void Key::pickUp(Player& player) { player.pickupKey(); }