#ifndef __PLAYER_DISCONNECT_H__
#define __PLAYER_DISCONNECT_H__

#include "Notification.h"

class PlayerDisconnect : public Notification {
 private:
  int playerID;

 public:
  PlayerDisconnect(int playerID);
  void send(SocketWrapper& socket);
};

#endif
