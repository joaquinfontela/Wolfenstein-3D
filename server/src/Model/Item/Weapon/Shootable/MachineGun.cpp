#include "../../../../../includes/Model/Item/StockableItem/Weapon/Shootable/MachineGun.h"

MachineGun::MachineGun(int newAmmo) : Shootable(newAmmo) {}

void MachineGun::shoot() {
  ammo -= 5;
  if (ammo < 0) ammo = 0;
}