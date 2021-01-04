#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(int newAmmo);
  ~Minigun();
  unsigned int attack();
};