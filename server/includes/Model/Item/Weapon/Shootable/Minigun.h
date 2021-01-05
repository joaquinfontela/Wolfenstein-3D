#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(unsigned int newAmmo) : Shootable(newAmmo) {}
  ~Minigun();
  unsigned int attack();
};