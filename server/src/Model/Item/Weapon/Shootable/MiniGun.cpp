#include "../../../../../includes/Model/Item/Weapon/Shootable/MiniGun.h"

MiniGun::MiniGun(int newAmmo) : Shootable(newAmmo) {}

MiniGun::~MiniGun() {}

unsigned int MiniGun::shoot() {
    // Deberia generar un numero aleatorio entre 1 y 10, y luego multiplicarlo por la cantidad de balas que se dispararon para devolver el daño que se haria.
  --ammo;

  return 0;
}
