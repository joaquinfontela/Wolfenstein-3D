#ifndef __KEY_H__
#define __KEY_H__

#include "Item.h"

class Key : public Item{


public:

  Key(int id);
  bool canBePickedUpBy(Player* p);
  void pickUp(Player* p);
};




#endif
