#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(int newAmmo);
  ~RocketLauncher();
  void shoot();
  bool outOfAmmo();
};