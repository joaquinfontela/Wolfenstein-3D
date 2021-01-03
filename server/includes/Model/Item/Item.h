#ifndef __ITEM_H__
#define __ITEM_H__

#include "../Player/Player.h"

class Item {
protected:

  int id;

public:

  Item(){}
  Item(int id) : id(id){}
  virtual bool canBePickedUpBy(Player* p) = 0;
  virtual void pickUp(Player* p) = 0;
  ~Item(){}
};





#endif
