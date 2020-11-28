#include "Shootable.h"

class MachineGun : public Shootable {
 public:
  MachineGun(int newAmmo);
  ~MachineGun();
  void shoot();
};