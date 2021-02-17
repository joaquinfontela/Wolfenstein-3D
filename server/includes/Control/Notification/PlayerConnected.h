#ifndef __PLAYER_CONNECTED_H__
#define __PLAYER_CONNECTED_H__
#include "../../../../common/includes/Socket/SocketCommunication.h"
#include "Notification.h"

class PlayerConnected : public Notification {
 private:
  int playerID;
  int x, y;

 public:
  PlayerConnected(int playerID, int x, int y);

  void send(SocketWrapper& socket);
};

#endif
