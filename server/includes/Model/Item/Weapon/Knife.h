#include "Weapon.h"

class Knife : public Weapon {
 public:
  Knife();
  ~Knife();
  unsigned int attack();
};
