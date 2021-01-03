#ifndef __BLOOD_H__
#define __BLOOD_H__

#include "Item.h"

class Blood : public Item{

public:

  Blood(int id);
  bool canBePickedUpBy(Player* p);
  void pickUp(Player* p);
};




#endif
