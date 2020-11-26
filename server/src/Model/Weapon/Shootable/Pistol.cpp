#include "../../../../includes/Model/Weapon/Shootable/Pistol.h"

Pistol::Pistol(int newAmmo) : Shootable(newAmmo) {}

void Pistol::shoot() { --ammo; }