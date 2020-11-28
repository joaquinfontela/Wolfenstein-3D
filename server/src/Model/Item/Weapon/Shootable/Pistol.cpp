#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

Pistol::Pistol(int newAmmo) : Shootable(newAmmo) {}

Pistol::~Pistol() {}

void Pistol::shoot() { --ammo; }