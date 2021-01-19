#ifndef __ITEM_H__
#define __ITEM_H__

#include "../Player/Player.h"
class Player;

class Item {
 protected:
  int id;
  int itemID;

 public:
  Item() {}
  Item(int itemID, int id) : id(id), itemID(itemID) {}
  int getID(){ return id;}
  int getItemID(){return itemID;}
  virtual bool canBePickedUpBy(Player* p) = 0;
  virtual void pickUp(Player* p) = 0;
  ~Item() {}
};

#endif
