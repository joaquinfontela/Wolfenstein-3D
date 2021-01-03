#ifndef __ITEM_H__
#define __ITEM_H__

#include "../Player/Player.h"

class Item {
protected:

  int id;

public:

  virtual bool canBePickedUpBy(Player* p);
  virtual void pickUp(Player* p);
};





#endif
