#include "Pistol.h"

Pistol::Pistol(int newAmmo) : Shootable(newAmmo) {}

void Pistol::shoot() { --ammo; }