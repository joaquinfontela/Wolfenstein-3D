#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(unsigned int newAmmo) : Shootable(newAmmo) {}
  ~RocketLauncher();
  unsigned int attack();
  bool outOfAmmo();
};