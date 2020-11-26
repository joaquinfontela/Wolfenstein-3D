#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(int newAmmo);
  void shoot();
  bool outOfAmmo();
};