#include "Shootable.h"

class Minigun : public Shootable {
 public:
  Minigun(unsigned int newAmmo) : Shootable(newAmmo), ID(3) {}
  ~Minigun();
  unsigned int attack();
  int getID();

private:
  int ID;
};
