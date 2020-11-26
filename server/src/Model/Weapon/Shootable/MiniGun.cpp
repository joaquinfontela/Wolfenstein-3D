#include "MiniGun.h"

MiniGun::MiniGun(int newAmmo) : Shootable(newAmmo) {}

void MiniGun::shoot() { --ammo; }