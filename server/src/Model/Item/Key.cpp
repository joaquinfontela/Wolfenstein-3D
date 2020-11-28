#include "../../../includes/Model/Item/Key.h"

Key::Key() : Item() {}

Key::~Key() {}

void Key::pickUp(Player& player) { player.pickupKey(); }