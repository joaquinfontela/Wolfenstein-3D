#include "../../../includes/Model/Item/Pistol.h"

Pistol::Pistol(unsigned int ammo) : Weapon(ammo){}


unsigned int Pistol::attack(){

  return 1;
}
