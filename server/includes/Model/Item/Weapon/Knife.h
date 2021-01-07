#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "Weapon.h"

class Knife : public Weapon {
 public:
  Knife() : ID(1) {}
  ~Knife();
  int getID();
  unsigned int attack();

private:
  int ID;
};

#endif
