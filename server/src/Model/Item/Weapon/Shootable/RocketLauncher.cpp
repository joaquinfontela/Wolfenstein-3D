#include "../../../../../includes/Model/Item/Weapon/Shootable/RocketLauncher.h"

RocketLauncher::RocketLauncher(int newAmmo) : Shootable(newAmmo) {}

RocketLauncher::~RocketLauncher() {}

unsigned int RocketLauncher::shoot() {
  ammo -= 5;
  // Caso Rocket Launcher no haria falta calcular ningun daño, ya que lo unico que hace es spawnear un rocket en el mapa.

  return 0;
 }

bool RocketLauncher::outOfAmmo() { return (ammo < 5); }
