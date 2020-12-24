#include "../../../../../includes/Model/Item/Weapon/Shootable/MachineGun.h"

MachineGun::MachineGun(int newAmmo) : Shootable(newAmmo) {}

MachineGun::~MachineGun() {}

unsigned int MachineGun::shoot() {
  ammo -= 5;
  if (ammo < 0) ammo = 0;

  return 0;
  // Deberia generar un numero aleatorio entre 1 y 10, y luego multiplicarlo por la cantidad de balas que se dispararon para devolver el daño que se haria.
}
