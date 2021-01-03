#ifndef __PISTOL_H__
#define __PISTOL_H__

#include "Weapon.h"

class Pistol : public Weapon{

public:

  Pistol(unsigned int ammo);

  unsigned int attack();

};





#endif
