#ifndef __PLAYER_DROP_ITEM_H__
#define __PLAYER_DROP_ITEM_H__

#include "Notification.h"

class PlayerDropItem : public Notification {
 private:
  int x, y;
  int itemID, uniqueId;

 public:
  PlayerDropItem(int x, int y, int itemId, int uniqueId);
  void send(SocketCommunication& socket);
};

#endif
