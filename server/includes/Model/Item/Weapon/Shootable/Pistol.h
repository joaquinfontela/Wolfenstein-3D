#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Shootable.h"

class Pistol : public Shootable {
 public:
  Pistol(unsigned int ammo) : Shootable(ammo), ID(3) {}
  int getID();

  // Devuelve el daño que haria el disparo.
  unsigned int attack();
  bool hasAmmo();

private:

  int ID;
};

#endif
