#include "../../../../includes/Model/Item/StockableItem/Weapon/Weapon.h"

void Weapon::stockItem(Player player) { player.equipWeapon(this); }