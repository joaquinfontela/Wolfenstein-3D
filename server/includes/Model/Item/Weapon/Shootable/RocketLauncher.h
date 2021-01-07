#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(unsigned int newAmmo) : Shootable(newAmmo), ID(5) {}
  ~RocketLauncher();
  unsigned int attack();
  bool hasAmmo();
  int getID();

private:
  int ID;
};
