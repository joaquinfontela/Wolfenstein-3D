#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Shootable.h"

class Pistol : public Shootable {
 public:
  Pistol(unsigned int ammo) : Shootable(ammo) {}

  // Devuelve el daño que haria el disparo.
  unsigned int attack();
};

#endif
