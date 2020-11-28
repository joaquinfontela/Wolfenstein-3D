#include "../../../../../includes/Model/Item/Weapon/Shootable/MiniGun.h"

MiniGun::MiniGun(int newAmmo) : Shootable(newAmmo) {}

MiniGun::~MiniGun() {}

void MiniGun::shoot() { --ammo; }