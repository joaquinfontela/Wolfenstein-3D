#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Weapon.h"

class Pistol : public Weapon {
 public:
  Pistol(unsigned int ammo);

  // Devuelve el daño que haria el disparo.
  unsigned int attack();
  bool outOfAmmo();
};

#endif
