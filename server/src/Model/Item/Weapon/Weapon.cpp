#include "../../../../includes/Model/Item/Weapon/Weapon.h"

unsigned int Weapon::getRandomDamage() { return ((rand() % 10) + 1); }