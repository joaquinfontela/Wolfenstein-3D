#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(unsigned int newAmmo) : Shootable(newAmmo) {}
  ~MachineGun();
  unsigned int attack();
};