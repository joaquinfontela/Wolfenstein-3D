#include "../../../../../includes/Model/Item/Weapon/Shootable/Pistol.h"

Pistol::Pistol(int newAmmo) : Shootable(newAmmo) {}

Pistol::~Pistol() {}

unsigned int Pistol::shoot() {
  --ammo;
  // Deberia generar un numero aleatorio entre 1 y 10, y luego multiplicarlo por la cantidad de balas que se dispararon para devolver el daño que se haria.
  return 0;
 }
