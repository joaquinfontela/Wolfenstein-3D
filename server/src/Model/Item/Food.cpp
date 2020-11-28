#include "../../../includes/Model/Item/Food.h"

Food::Food() : Item() {}

Food::~Food() {}

void Food::pickUp(Player& player) { player.addHealth(10); }