#include "../../../../includes/Model/Item/Weapon/Knife.h"

Knife::Knife() : Weapon() {}

Knife::~Knife() {}

unsigned int Knife::attack() {return 100; // Deberia devolver el daño fijo del cuchillo}
