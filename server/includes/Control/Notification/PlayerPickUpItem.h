#ifndef __PLAYER_PICKUP_ITEM_H__
#define __PLAYER_PICKUP_ITEM_H__

#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class PlayerPickupItem : public Notification {
 private:
   int uniqueId;

 public:
  PlayerPickupItem(int uniqueId);

  void send(SocketWrapper& socket);
};

#endif
