#include "../../../../../../includes/Model/Item/StockableItem/Weapon/Shootable/MiniGun.h"

MiniGun::MiniGun(int newAmmo) : Shootable(newAmmo) {}

void MiniGun::shoot() { --ammo; }