#include "Shootable.h"

class Pistol : public Shootable {
 public:
  Pistol(int newAmmo);
  ~Pistol();
  unsigned int shoot();
};
