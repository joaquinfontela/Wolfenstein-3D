#include "../../../../includes/Model/Item/Weapon/Weapon.h"

void Weapon::pickUp(Player player) { player.equipWeapon(this); }