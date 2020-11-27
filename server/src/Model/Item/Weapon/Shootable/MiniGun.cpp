#include "../../../../../includes/Model/Item/Weapon/Shootable/MiniGun.h"

MiniGun::MiniGun(int newAmmo) : Shootable(newAmmo) {}

void MiniGun::shoot() { --ammo; }