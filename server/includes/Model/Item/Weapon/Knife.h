#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "Weapon.h"

class Knife : public Weapon {
 public:
  Knife() {}
  ~Knife();
  unsigned int attack();
};

#endif